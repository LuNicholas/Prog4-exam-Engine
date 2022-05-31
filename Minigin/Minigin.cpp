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
#include "Enemy.h"



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
	Texture2DComponent* levelTexture = levelGO->AddComponent<Texture2DComponent>();
	levelTexture->SetTexture("level1.png");
	levelTexture->SetPosition(0, 700 - 600);
	scene.Add(levelGO);


	//fps game object
	auto fpsGo = std::make_shared<GameObject>();
	FpsComponent* fpsComponent = fpsGo->AddComponent<FpsComponent>();
	fpsComponent->SetPosition(10, 10);
	fpsComponent->SetFont(font);
	scene.Add(fpsGo);


	//new peter pepper
	auto peterPepperGo = std::make_shared<GameObject>();
	PeterPepper* peterComp = peterPepperGo->AddComponent<PeterPepper>();
	peterComp->Init();
	peterPepperGo->SetPosition(300, 540);

	//adding animation
	//AnimationManager* peterAnimManager = peterPepperGo->AddComponent<AnimationManager>();
	//peterAnimManager->AddAnimation("Peter_Up.png", "up", 96, 32, 3, 1, 0.5f);
	//peterAnimManager->AddAnimation("Peter_Forward.png", "forward", 96, 32, 3, 1, 0.5f);
	//peterAnimManager->AddAnimation("Peter_Left.png", "left", 96, 32, 3, 1, 0.5f);
	//peterAnimManager->AddAnimation("Peter_Right.png", "right", 96, 32, 3, 1, 0.5f);
	//peterAnimManager->AddAnimation("forward_Idle.png", "idleForward", 32, 32, 1, 1, -1);
	//peterAnimManager->AddAnimation("up_Idle.png", "idleUp", 32, 32, 1, 1, -1);
	//peterAnimManager->SetActiveAnimation("idleForward");



	//adding peter collision box
	//CollisionBox* ppBox = peterPepperGo->AddComponent<CollisionBox>();
	//ppBox->SetTag("Player");
	//ppBox->SetBox(32, 32);

	scene.Add(peterPepperGo);


	input.AddCommand(dae::ControllerButton::DpadLeft, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveLeft>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadRight, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveRight>(peterPepperGo)), 0);



	//UI
	auto UiPeter = std::make_shared<GameObject>();
	PlayerUiComponent* peterUiComp = UiPeter->AddComponent<PlayerUiComponent>();
	peterUiComp->SetFont(font);
	peterUiComp->SetLives(peterComp->GetHealth()->GetHealth());
	peterUiComp->SetLives(3);
	peterUiComp->SetPosition(450, 10);
	scene.Add(UiPeter);
	peterComp->GetHealth()->addObserver(peterUiComp);

	//peterCommand
	input.AddCommand(dae::ControllerButton::ButtonA, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<HitCommand>(peterPepperGo.get())), 0);

	std::unique_ptr<BunDropped> scorePeterCommand = std::make_unique<BunDropped>(peterPepperGo.get());
	scorePeterCommand->addObserver(peterUiComp);
	input.AddCommand(dae::ControllerButton::ButtonY, dae::ButtonActivateState::OnButtonRelease, std::move(scorePeterCommand), 0);

	input.AddCommand(dae::ControllerButton::DpadUp, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveUp>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadDown, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveDown>(peterPepperGo)), 0);

	input.AddCommand(dae::ControllerButton::DpadUp, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleUp>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadDown, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleForward>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadLeft, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleForward>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadRight, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleForward>(peterPepperGo)), 0);



	//second player
	/*

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

	*/


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



	//LEVEL COLLISION 
	//LEVEL FLOORS
	{
		int floorWidth = 13;
		auto levelFloor = std::make_shared<GameObject>();
		CollisionBox* floor1 = levelFloor->AddComponent<CollisionBox>();
		floor1->SetTag("floor");
		floor1->SetPosition(5, 565);
		floor1->SetBox(613, floorWidth);

		CollisionBox* floor2 = levelFloor->AddComponent<CollisionBox>();
		floor2->SetTag("floor");
		floor2->SetPosition(5, 469);
		floor2->SetBox(470, floorWidth);

		CollisionBox* floor3 = levelFloor->AddComponent<CollisionBox>();
		floor3->SetTag("floor");
		floor3->SetPosition(438, 420);
		floor3->SetBox(180, floorWidth);

		CollisionBox* floor4 = levelFloor->AddComponent<CollisionBox>();
		floor4->SetTag("floor");
		floor4->SetPosition(150, 373);
		floor4->SetBox(325, floorWidth);

		CollisionBox* floor5 = levelFloor->AddComponent<CollisionBox>();
		floor5->SetTag("floor");
		floor5->SetPosition(5, 325);
		floor5->SetBox(180, floorWidth);


		CollisionBox* floor6 = levelFloor->AddComponent<CollisionBox>();
		floor6->SetTag("floor");
		floor6->SetPosition(438, 325);
		floor6->SetBox(180, floorWidth);

		CollisionBox* floor7 = levelFloor->AddComponent<CollisionBox>();
		floor7->SetTag("floor");
		floor7->SetPosition(150, 277);
		floor7->SetBox(180, floorWidth);

		CollisionBox* floor8 = levelFloor->AddComponent<CollisionBox>();
		floor8->SetTag("floor");
		floor8->SetPosition(5, 230);
		floor8->SetBox(180, floorWidth);

		CollisionBox* floor9 = levelFloor->AddComponent<CollisionBox>();
		floor9->SetTag("floor");
		floor9->SetPosition(292, 230);
		floor9->SetBox(325, floorWidth);

		CollisionBox* floor10 = levelFloor->AddComponent<CollisionBox>();
		floor10->SetTag("floor");
		floor10->SetPosition(5, 133);
		floor10->SetBox(613, floorWidth);

		scene.Add(levelFloor);

	}

	//LEVEL LADDERS
	{
		//testLadder
		int ladderWidth = 10;
		auto ladderGO = std::make_shared<GameObject>();
		CollisionBox* ladder1 = ladderGO->AddComponent<CollisionBox>();
		ladder1->SetTag("Ladder");
		ladder1->SetPosition(18, 300);
		ladder1->SetBox(ladderWidth, 271);

		CollisionBox* ladder2 = ladderGO->AddComponent<CollisionBox>();
		ladder2->SetTag("Ladder");
		ladder2->SetPosition(18, 108);
		ladder2->SetBox(ladderWidth, 130);

		CollisionBox* ladder3 = ladderGO->AddComponent<CollisionBox>();
		ladder3->SetTag("Ladder");
		ladder3->SetPosition(90, 205);
		ladder3->SetBox(ladderWidth, 271);

		CollisionBox* ladder4 = ladderGO->AddComponent<CollisionBox>();
		ladder4->SetTag("Ladder");
		ladder4->SetPosition(164, 109);
		ladder4->SetBox(ladderWidth, 462);

		CollisionBox* ladder5 = ladderGO->AddComponent<CollisionBox>();
		ladder5->SetTag("Ladder");
		ladder5->SetPosition(235, 109);
		ladder5->SetBox(ladderWidth, 176);

		CollisionBox* ladder6 = ladderGO->AddComponent<CollisionBox>();
		ladder6->SetTag("Ladder");
		ladder6->SetPosition(307, 109);
		ladder6->SetBox(ladderWidth, 462);

		CollisionBox* ladder7 = ladderGO->AddComponent<CollisionBox>();
		ladder7->SetTag("Ladder");
		ladder7->SetPosition(380, 205);
		ladder7->SetBox(ladderWidth, 176);

		CollisionBox* ladder8 = ladderGO->AddComponent<CollisionBox>();
		ladder8->SetTag("Ladder");
		ladder8->SetPosition(450, 109);
		ladder8->SetBox(ladderWidth, 462);

		CollisionBox* ladder9 = ladderGO->AddComponent<CollisionBox>();
		ladder9->SetTag("Ladder");
		ladder9->SetPosition(523, 300);
		ladder9->SetBox(ladderWidth, 271);

		CollisionBox* ladder10 = ladderGO->AddComponent<CollisionBox>();
		ladder10->SetTag("Ladder");
		ladder10->SetPosition(595, 396);
		ladder10->SetBox(ladderWidth, 175);

		CollisionBox* ladder11 = ladderGO->AddComponent<CollisionBox>();
		ladder11->SetTag("Ladder");
		ladder11->SetPosition(595, 109);
		ladder11->SetBox(ladderWidth, 222);

		scene.Add(ladderGO);
	}

	//first burger
	{
		//add burgers
		auto topBunGo = std::make_shared<GameObject>();
		topBunGo->SetPosition(50, 210);
		Bun* topBun = topBunGo->AddComponent<Bun>();
		topBun->Init("bun.png");
		scene.Add(topBunGo);

		auto midBunGo = std::make_shared<GameObject>();
		midBunGo->SetPosition(50, 290);
		Bun* midBun = midBunGo->AddComponent<Bun>();
		midBun->Init("salad.png");
		scene.Add(midBunGo);

		auto mid2BunGo = std::make_shared<GameObject>();
		mid2BunGo->SetPosition(50, 435);
		Bun* mid2Bun = mid2BunGo->AddComponent<Bun>();
		mid2Bun->Init("patty.png");
		scene.Add(mid2BunGo);

		//auto botBunGo = std::make_shared<GameObject>();
		//botBunGo->SetPosition(50, 530);
		//Bun* botBun = botBunGo->AddComponent<Bun>();
		//botBun->Init("bun_Bottom.png");
		//scene.Add(botBunGo);

		//ADDING TESTPLATE
		auto plate1 = std::make_shared<GameObject>();
		CollisionBox* floor6 = plate1->AddComponent<CollisionBox>();
		floor6->SetTag("plate");
		floor6->SetPosition(38, 695);
		floor6->SetBox(20, 10);
		scene.Add(plate1);

		topBun->addObserver(peterUiComp);
		midBun->addObserver(peterUiComp);
		mid2Bun->addObserver(peterUiComp);
		//botBun->addObserver(peterUiComp);
	}



	//enemy test
	auto enemyGO = std::make_shared<GameObject>();
	Enemy* enemy = enemyGO->AddComponent<Enemy>();
	enemy->Init();
	enemyGO->SetPosition(60, 540);
	enemy->AddPlayer(peterComp);
	scene.Add(enemyGO);

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
