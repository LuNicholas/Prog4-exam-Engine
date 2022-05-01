#include "MiniginPCH.h"
#include "Sound.h"
#include <map>
#include <thread>
#include <mutex>
#include <condition_variable>


SoundSystem* SoundServiceLocator::m_SoundSystemInstance{};
NullSound SoundServiceLocator::m_NullSound{};

SoundServiceLocator::~SoundServiceLocator()
{
}



//Pimpl
class SDLSoundSystem::SoundSystemImpl
{
public:
	SoundSystemImpl();
	~SoundSystemImpl();

	void Play(const soundId soundId, const float volume);
	void RegisterSound(const soundId soundId, const std::string& path);

	void Update();
private:
	int m_Frequequency = 22050;
	Uint16 m_Format = AUDIO_S16SYS;
	int m_Channels = 2;
	int m_ChunkSize = 4096;

	int m_Head;
	int m_Tail;
	std::map<soundId, Mix_Chunk*> m_SoundBank;
	static const int m_MaxQueueSize = 10;
	SoundInfo m_SoundQueue[m_MaxQueueSize];

	std::jthread m_UpdateThread;
	std::mutex m_MutexUpdate;
	std::condition_variable m_CvUpdate;
	bool m_IsActiveThread;
};

SDLSoundSystem::SoundSystemImpl::SoundSystemImpl()
	:m_SoundQueue{}
	, m_Head{ 0 }
	, m_Tail{ 0 }
	, m_UpdateThread{}
	, m_IsActiveThread{ true }
{
	SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudio(m_Frequequency, m_Format, m_Channels, m_ChunkSize) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failure init audio %s", Mix_GetError());
	}

	m_UpdateThread = std::jthread([this]
		{
			while (m_IsActiveThread)
			{
				std::unique_lock<std::mutex> lk(m_MutexUpdate);
				m_CvUpdate.wait(lk, [this]
					{
						return (m_Head != m_Tail);
					});
				Update();
			}
		});
}
SDLSoundSystem::SoundSystemImpl::~SoundSystemImpl()
{
	m_IsActiveThread = false;
	m_UpdateThread.join();

	Mix_CloseAudio();
	Mix_Quit();
}

void SDLSoundSystem::SoundSystemImpl::Play(const soundId soundId, const float volume)
{
	assert((m_Tail + 1) % m_MaxQueueSize != m_Head);

	m_SoundQueue[m_Tail].id = soundId;
	m_SoundQueue[m_Tail].volume = volume;
	m_Tail = (m_Tail + 1) % m_MaxQueueSize;

	m_CvUpdate.notify_all();
}
void SDLSoundSystem::SoundSystemImpl::RegisterSound(const soundId soundId, const std::string& path)
{
	Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
	if (chunk != nullptr)
	{
		m_SoundBank[soundId] = chunk;
	}
}
void SDLSoundSystem::SoundSystemImpl::Update()
{
	if (m_Head == m_Tail)
		return;

	Mix_Chunk* pCurrentChunk = m_SoundBank[m_SoundQueue[m_Head].id];
	Mix_VolumeChunk(pCurrentChunk, m_SoundQueue[m_Head].volume);
	Mix_PlayChannel(-1, pCurrentChunk, 0);
	m_Head = (m_Head + 1) % m_MaxQueueSize;
}

//SDL soundsystem
SDLSoundSystem::SDLSoundSystem()
{
	m_pImpl = new SoundSystemImpl();
}
SDLSoundSystem::~SDLSoundSystem()
{
}

void SDLSoundSystem::Play(const soundId soundId, const float volume)
{
	m_pImpl->Play(soundId, volume);
}
void SDLSoundSystem::RegisterSound(const soundId soundId, const std::string& path)
{

	m_pImpl->RegisterSound(soundId, path);
}

void SDLSoundSystem::Update()
{
	m_pImpl->Update();
}




//logging
LoggingSoundSystem::LoggingSoundSystem(SoundSystem* ss)
	: m_SoundSystem(ss)
{}
LoggingSoundSystem::~LoggingSoundSystem()
{
	delete m_SoundSystem;
}