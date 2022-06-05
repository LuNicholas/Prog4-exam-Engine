#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Texture2DComponent.h"
#include "ImguiExerciseComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "Component.h"
#include "FpsComponent.h"
#include "AnimationManager.h"
#include "Sound.h"
#include "CollisionBox.h"



using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		624,
		700,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
}

void dae::Minigin::Cleanup()
{

	SoundServiceLocator::RegisterSoundSystem(nullptr);
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	//Initialize();

	// tell the resource manager where he can find the game data
	//ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();



		// todo: this update loop could use some work.
		bool doContinue = true;
		auto lastTime = chrono::high_resolution_clock::now();
		float lag = 0.0f;
		float fixedTimeStep = 0.02f;
		while (doContinue)
		{

			//time
			const auto currentTime = chrono::high_resolution_clock::now();
			float deltaTime = chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += deltaTime;


			doContinue = input.ProcessInput();
			input.CheckInput();


			while (lag >= fixedTimeStep)
			{
				sceneManager.FixedUpdate(deltaTime);
				lag -= fixedTimeStep;
			}

			sceneManager.Update(deltaTime);
			renderer.Render();

		}
	}

	//Cleanup();
}
