#pragma once
#include <SDL_mixer.h>

using soundId = unsigned short;

struct SoundInfo
{
	soundId id;
	int volume;
};

class SoundSystem
{
public:
	virtual ~SoundSystem() = default;
	virtual void Play(const soundId soundId, const float volume) = 0;
	virtual void RegisterSound(const soundId soundId, const std::string& path) = 0;
	virtual void Update() = 0;
private:
};

class SDLSoundSystem : public SoundSystem
{
	class SoundSystemImpl;
	SoundSystemImpl* m_pImpl;

public:
	SDLSoundSystem();
	~SDLSoundSystem();

	void Play(const soundId soundId, const float volume);
	void RegisterSound(const soundId soundId, const std::string& path);

	void Update();


private:
};

class NullSound final : public SoundSystem
{
public:
	virtual void Play(const soundId soundId, const float volume) {}
	virtual void RegisterSound(const soundId soundId, const std::string& path) {};
	virtual void Update() {};
};


class SoundServiceLocator final
{
	static SoundSystem* m_SoundSystemInstance;
	static NullSound m_NullSound;

public:
	~SoundServiceLocator();

	static SoundSystem& GetSoundSystem() { return *m_SoundSystemInstance; }

	static void RegisterSoundSystem(SoundSystem* ss)
	{
		if (m_SoundSystemInstance != &m_NullSound)
			delete m_SoundSystemInstance;


		if (ss == nullptr)
		{
			m_SoundSystemInstance = &m_NullSound;
		}
		else
		{
			m_SoundSystemInstance = ss;
		}
	}
};

class LoggingSoundSystem final : public SoundSystem
{
	SoundSystem* m_SoundSystem;
public:
	LoggingSoundSystem(SoundSystem* ss);
	~LoggingSoundSystem();

	void Play(const soundId soundId, const float volume)
	{
		m_SoundSystem->Play(soundId, volume);
		std::cout << "playing " << soundId << " at volume " << volume << std::endl;
	}
	void RegisterSound(const soundId id, const std::string& path)
	{
		m_SoundSystem->RegisterSound(id, path);
	}
	void Update()
	{
		m_SoundSystem->Update();
	}
};