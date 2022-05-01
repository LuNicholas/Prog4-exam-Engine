#include "MiniginPCH.h"
#include "Sound.h"


SoundSystem* SoundServiceLocator::m_SoundSystemInstance{};
NullSound SoundServiceLocator::m_NullSound{};

//int SDLSoundSystem::m_Head{ 0 };
//int SDLSoundSystem::m_Tail{ 0 };

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


	std::vector<Mix_Chunk*> m_SoundBank;
	const int m_MaxQueue = 10;
	SoundInfo m_SoundQueue[10];
	int m_CurrentQueueSize = 0;
};

SDLSoundSystem::SoundSystemImpl::SoundSystemImpl()
	:m_SoundQueue{}
{
	SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudio(m_Frequequency, m_Format, m_Channels, m_ChunkSize) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failure init audio %s", Mix_GetError());
	}
}
SDLSoundSystem::SoundSystemImpl::~SoundSystemImpl()
{
}

void SDLSoundSystem::SoundSystemImpl::Play(const soundId soundId, const float volume)
{
	if (m_CurrentQueueSize > m_MaxQueue)
		return;

	m_SoundQueue[m_CurrentQueueSize].id = soundId;
	m_SoundQueue[m_CurrentQueueSize].volume = volume;
	m_CurrentQueueSize++;

}
void SDLSoundSystem::SoundSystemImpl::RegisterSound(const soundId soundId, const std::string& path)
{
	Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
	if (chunk != nullptr)
	{
		m_SoundBank.insert(m_SoundBank.begin() + soundId, chunk);
	}
}
void SDLSoundSystem::SoundSystemImpl::Update()
{
	for (int i = 0; i < m_CurrentQueueSize; i++)
	{
		Mix_Volume(-1, m_SoundQueue[i].volume);
		Mix_PlayChannel(-1, m_SoundBank.at(m_SoundQueue[i].id), 0);
	}

	m_CurrentQueueSize = 0;
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
	//if (m_CurrentQueueSize > m_MaxQueue)
	//	return;

	//m_SoundQueue[m_CurrentQueueSize].id = soundId;
	//m_SoundQueue[m_CurrentQueueSize].volume = volume;
	//m_CurrentQueueSize++;

	m_pImpl->Play(soundId, volume);
}
void SDLSoundSystem::RegisterSound(const soundId soundId, const std::string& path)
{
	//const char* test = path.c_str();

	//Mix_Chunk* chunk = Mix_LoadWAV(test);
	//if (chunk != nullptr)
	//{
	//	m_SoundBank.insert(m_SoundBank.begin() + soundId, chunk);
	//}

	m_pImpl->RegisterSound(soundId, path);
}

void SDLSoundSystem::Update()
{
	//for (int i = 0; i < m_CurrentQueueSize; i++)
	//{
	//	Mix_Volume(-1, m_SoundQueue[i].volume);
	//	Mix_PlayChannel(-1, m_SoundBank.at(m_SoundQueue[i].id), 0);
	//}

	//m_CurrentQueueSize = 0;
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