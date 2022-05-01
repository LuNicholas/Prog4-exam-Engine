#include "MiniginPCH.h"
#include "Sound.h"


SoundSystem* SoundServiceLocator::m_SoundSystemInstance{};
NullSound SoundServiceLocator::m_NullSound{};

int SDLSoundSystem::m_Head{ 0 };
int SDLSoundSystem::m_Tail{ 0 };

SoundServiceLocator::~SoundServiceLocator()
{
}


//SDL soundsystem
SDLSoundSystem::SDLSoundSystem()
	:m_SoundQueue{}
{

	SDL_Init(SDL_INIT_AUDIO);
	if (Mix_OpenAudio(m_Frequequency, m_Format, m_Channels, m_ChunkSize) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "failure init audio %s", Mix_GetError());
	}
}
SDLSoundSystem::~SDLSoundSystem()
{
}

void SDLSoundSystem::Play(const soundId soundId, const float volume)
{
	//if (soundId > m_SoundBank.size() - 1)
	//	return;

	//Mix_PlayChannel(-1, m_SoundBank[soundId], 0);

	if (m_CurrentQueueSize > m_MaxQueue)
		return;

	m_SoundQueue[m_CurrentQueueSize].id = soundId;
	m_SoundQueue[m_CurrentQueueSize].volume = volume;
	m_CurrentQueueSize++;

}
void SDLSoundSystem::RegisterSound(const soundId soundId, const std::string& path)
{
	const char* test = path.c_str();

	Mix_Chunk* chunk = Mix_LoadWAV(test);
	if (chunk != nullptr)
	{
		m_SoundBank.insert(m_SoundBank.begin() + soundId, chunk);
	}
}

void SDLSoundSystem::Update()
{
	for (int i = 0; i < m_CurrentQueueSize; i++)
	{
		Mix_Volume(-1, m_SoundQueue[i].volume);
		Mix_PlayChannel(-1, m_SoundBank.at(m_SoundQueue[i].id), 0);
	}

	m_CurrentQueueSize = 0;
}

//logging
LoggingSoundSystem::LoggingSoundSystem(SoundSystem* ss)
	: m_SoundSystem(ss)
{}
LoggingSoundSystem::~LoggingSoundSystem()
{
	delete m_SoundSystem;
}