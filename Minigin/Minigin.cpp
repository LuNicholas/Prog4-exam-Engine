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
#include "PlayerUiComponent.h"
//#include "SpriteAnimation.h"
#include "AnimationManager.h"
#include "PeterPepper.h"
#include "Sound.h"
#include "CollisionBox.h"
#include "Bun.h"



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
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	auto& input = InputManager::GetInstance();

	auto go = std::make_shared<GameObject>();
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//levelsprite
	auto levelGO = std::make_shared<GameObject>();
	levelGO->AddComponent<Texture2DComponent>()->SetTexture("testLevel.png");
	Texture2DComponent* levelTexture = levelGO->AddComponent<Texture2DComponent>();
	levelTexture->SetTexture("testLevel.png");
	levelTexture->SetPosition(0, 700 - 600);
	scene.Add(levelGO);


	//fps game object
	auto fpsGo = std::make_shared<GameObject>();
	FpsComponent* fpsComponent = fpsGo->AddComponent<FpsComponent>();
	fpsComponent->SetPosition(300, 100);
	fpsComponent->SetFont(font);
	scene.Add(fpsGo);


	//new peter pepper
	auto peterPepperGo = std::make_shared<GameObject>();
	PeterPepper* peterComp = peterPepperGo->AddComponent<PeterPepper>();
	peterPepperGo->SetPosition(175, 295);

	//adding animation
	AnimationManager* peterAnimManager = peterPepperGo->AddComponent<AnimationManager>();
	peterAnimManager->AddAnimation("Peter_Up.png", "up", 144, 48, 3, 1, 0.5f);
	peterAnimManager->AddAnimation("Peter_Forward.png", "forward", 144, 48, 3, 1, 0.5f);
	peterAnimManager->AddAnimation("Peter_Left.png", "left", 144, 48, 3, 1, 0.5f);
	peterAnimManager->AddAnimation("Peter_Right.png", "right", 144, 48, 3, 1, 0.5f);
	peterAnimManager->SetActiveAnimation("forward");



	//adding collision box
	CollisionBox* ppBox = peterPepperGo->AddComponent<CollisionBox>();
	ppBox->SetTag("Player");
	ppBox->SetBox(48 + 2, 48 + 2);

	scene.Add(peterPepperGo);


	std::unique_ptr<MoveLeft> moveLeft = std::make_unique<MoveLeft>(peterPepperGo);
	input.AddCommand(dae::ControllerButton::DpadLeft, dae::ButtonActivateState::IsPressed, std::move(moveLeft), 0);
	std::unique_ptr<MoveRight> moveRight = std::make_unique<MoveRight>(peterPepperGo);
	input.AddCommand(dae::ControllerButton::DpadRight, dae::ButtonActivateState::IsPressed, std::move(moveRight), 0);


	//test collision box
	auto tesgo = std::make_shared<GameObject>();
	CollisionBox* idk = tesgo->AddComponent<CollisionBox>();
	idk->SetTag("floor");
	idk->SetPosition(0, 340);
	idk->SetBox(500, 10);

	CollisionBox* idk2 = tesgo->AddComponent<CollisionBox>();
	idk2->SetTag("floor");
	idk2->SetPosition(0, 450);
	idk2->SetBox(500, 10);
	scene.Add(tesgo);



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



	//testLadder
	auto ladderGO = std::make_shared<GameObject>();
	CollisionBox* coll = ladderGO->AddComponent<CollisionBox>();
	coll->SetTag("Ladder");
	coll->SetBox(12, 200);
	coll->SetPosition(300, 280);
	scene.Add(ladderGO);

	std::unique_ptr<MoveUp> moveUp= std::make_unique<MoveUp>(peterPepperGo);
	input.AddCommand(dae::ControllerButton::DpadUp, dae::ButtonActivateState::IsPressed, std::move(moveUp), 0);
	std::unique_ptr<MoveDown> moveDown = std::make_unique<MoveDown>(peterPepperGo);
	input.AddCommand(dae::ControllerButton::DpadDown, dae::ButtonActivateState::IsPressed, std::move(moveDown), 0);





	std::cout << "\n Button A :Lose live\n Button Y: add score \n";


	///BUN TEST
	auto bunGO = std::make_shared<GameObject>();
	bunGO->SetPosition(50, 300);
	Bun* bun = bunGO->AddComponent<Bun>();
	bun->Init();
	Texture2DComponent* bunTexture = bunGO->AddComponent<Texture2DComponent>();
	bunTexture->SetTexture("bun.png");

	scene.Add(bunGO);

	///BUN TEST2
	auto bunGO2 = std::make_shared<GameObject>();
	bunGO2->SetPosition(50, 400);
	Bun* bunWHO = bunGO2->AddComponent<Bun>();
	bunWHO->Init();
	Texture2DComponent* bunTexture = bunGO->AddComponent<Texture2DComponent>();
	bunTexture->SetTexture("bun.png");
	scene.Add(bunGO2);



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
