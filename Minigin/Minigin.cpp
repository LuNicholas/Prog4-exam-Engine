#include "MiniginPCH.h"
#include "Minigin.h"
#include <steam_api.h>
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
#include "PlayerUiComponent.h"
#include "AnimationComponent.h"
#include "PeterPepper.h"
#include "Sound.h"



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
		640,
		480,
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
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	auto& input = InputManager::GetInstance();

	auto go = std::make_shared<GameObject>();
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	TextComponent* titleText = go->AddComponent<TextComponent>();
	titleText->SetText("Programming 4 Assignment");
	titleText->SetFont(font);
	titleText->SetPosition(100, 30);

	Texture2DComponent* texture = go->AddComponent<Texture2DComponent>();
	texture->SetTexture("logo.png");
	texture->SetPosition(216, 180);

	//fps game object
	auto fpsGo = std::make_shared<GameObject>();
	FpsComponent* fpsComponent = fpsGo->AddComponent<FpsComponent>();
	fpsComponent->SetPosition(300, 100);
	fpsComponent->SetFont(font);
	scene.Add(fpsGo);


	//test
	auto testAnim = std::make_shared<GameObject>();
	testAnim->SetPosition(150, 100);
	SpriteAnimationComponent* spriteAnim = testAnim->AddComponent<SpriteAnimationComponent>();
	spriteAnim->SetTexture("Peter_Forward.png");
	spriteAnim->SetRowCol(1, 3);
	spriteAnim->SetTextureSize(48, 16);
	spriteAnim->SetFrameTime(0.5f);
	scene.Add(testAnim);

	std::unique_ptr<MoveLeft> moveLeft = std::make_unique<MoveLeft>(testAnim);
	input.AddCommand(dae::ControllerButton::DpadLeft, dae::ButtonActivateState::IsPressed, std::move(moveLeft), 0);
	std::unique_ptr<MoveRight> moveRight = std::make_unique<MoveRight>(testAnim);
	input.AddCommand(dae::ControllerButton::DpadRight, dae::ButtonActivateState::IsPressed, std::move(moveRight), 0);

	//new peter pepper
	auto peterPepperGo = std::make_shared<GameObject>();
	PeterPepper* peterComp = peterPepperGo->AddComponent<PeterPepper>();
	scene.Add(peterPepperGo);


	//UI
	auto UiPeter = std::make_shared<GameObject>();
	PlayerUiComponent* peterUiComp = UiPeter->AddComponent<PlayerUiComponent>();
	peterUiComp->SetFont(font);
	peterUiComp->SetLives(peterComp->GetHealth()->GetHealth());
	peterUiComp->SetLives(3);
	peterUiComp->SetPosition(10, 400);
	scene.Add(UiPeter);

	peterComp->GetHealth()->addObserver(peterUiComp);

	//peterCommand
	std::unique_ptr<HitCommand> hitPeterCommand = std::make_unique<HitCommand>(peterPepperGo.get());
	input.AddCommand(dae::ControllerButton::ButtonA, dae::ButtonActivateState::OnButtonRelease, std::move(hitPeterCommand), 0);

	std::unique_ptr<BunDropped> scorePeterCommand = std::make_unique<BunDropped>(peterPepperGo.get());
	scorePeterCommand->addObserver(peterUiComp);
	input.AddCommand(dae::ControllerButton::ButtonY, dae::ButtonActivateState::OnButtonRelease, std::move(scorePeterCommand), 0);




	//sally salt
	auto sallySaltGo = std::make_shared<GameObject>();
	PeterPepper* sallyComp = sallySaltGo->AddComponent<PeterPepper>();
	scene.Add(sallySaltGo);


	//UI
	auto UiSally = std::make_shared<GameObject>();
	PlayerUiComponent* sallyUiComp = UiSally->AddComponent<PlayerUiComponent>();
	sallyUiComp->SetFont(font);
	sallyUiComp->SetLives(sallyComp->GetHealth()->GetHealth());
	sallyUiComp->SetLives(3);
	sallyUiComp->SetPosition(10, 325);
	scene.Add(UiSally);

	sallyComp->GetHealth()->addObserver(sallyUiComp);

	//sallyCommand
	std::unique_ptr<HitCommand> hitSallyCommand = std::make_unique<HitCommand>(sallySaltGo.get());
	input.AddCommand(dae::ControllerButton::ButtonA, dae::ButtonActivateState::OnButtonRelease, std::move(hitSallyCommand), 1);

	std::unique_ptr<BunDropped> scoreSallyCommand = std::make_unique<BunDropped>(sallySaltGo.get());
	scoreSallyCommand->addObserver(sallyUiComp);
	input.AddCommand(dae::ControllerButton::ButtonY, dae::ButtonActivateState::OnButtonRelease, std::move(scoreSallyCommand), 1);



	std::cout << "\n Button A :Lose live\n Button Y: add score \n";



	//SOUND

#if _DEBUG
	SoundServiceLocator::RegisterSoundSystem(new LoggingSoundSystem(new SDLSoundSystem()));
#else
	SoundServiceLocator::RegisterSoundSystem(new SDLSoundSystem());
#endif // _DEBUG


	
	SoundServiceLocator::GetSoundSystem().RegisterSound(0, "../Data/meow1.wav");
	std::unique_ptr<PlaySound> playMeow = std::make_unique<PlaySound>(0);
	input.AddCommand(dae::ControllerButton::ButtonB, dae::ButtonActivateState::OnButtonRelease, std::move(playMeow), 0);

	std::cout << "\n\n Button B :PLAY SOUND\n";


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
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

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
			SteamAPI_RunCallbacks();

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

	Cleanup();
}
