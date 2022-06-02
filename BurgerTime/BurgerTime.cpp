#include "BurgerTimePCH.h"
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Texture2DComponent.h"
#include "ResourceManager.h"
#include "Texture2DComponent.h"
#include "FpsComponent.h"
#include "PeterPepper.h"
#include "Pepper.h"
#include "PlayerUiComponent.h"
#include "GameCommands.h"
#include "Sound.h"
#include "CollisionBox.h"
#include "Ingredient.h"
#include "Enemy.h"
#include "AnimationManager.h"


void Level1();
void Test();

int main(int, char* [])
{
	dae::Minigin engine;
	engine.Initialize();
	dae::ResourceManager::GetInstance().Init("../Data/");///////COMMENTED SHIT IN MINIGIN THISH THISH 

	Test();
	Level1();

	dae::SceneManager::GetInstance().SetActiveScene("level1");

	engine.Run();

	engine.Cleanup();
	return 0;
}

void Test()
{

	auto& scene = dae::SceneManager::GetInstance().CreateScene("testLevel");
	auto& input = dae::InputManager::GetInstance();

	//levelsprite
	auto levelGO = std::make_shared<dae::GameObject>();
	dae::Texture2DComponent* levelTexture = levelGO->AddComponent<dae::Texture2DComponent>();
	levelTexture->SetTexture("level1.png");
	levelTexture->SetPosition(0, 0);
	scene.Add(levelGO);


	input.AddCommand(dae::ControllerButton::ButtonX, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<NextScene>()), 0);
}

void Level1()
{
	

	auto& scene = dae::SceneManager::GetInstance().CreateScene("level1");
	//dae::SceneManager::GetInstance().SetActiveScene("level1");
	auto& input = dae::InputManager::GetInstance();


	auto go = std::make_shared<dae::GameObject>();
	scene.Add(go);


	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//levelsprite
	auto levelGO = std::make_shared<dae::GameObject>();
	dae::Texture2DComponent* levelTexture = levelGO->AddComponent<dae::Texture2DComponent>();
	levelTexture->SetTexture("level1.png");
	levelTexture->SetPosition(0, 700 - 600);
	scene.Add(levelGO);


	//fps game object
	auto fpsGo = std::make_shared<dae::GameObject>();
	dae::FpsComponent* fpsComponent = fpsGo->AddComponent<dae::FpsComponent>();
	fpsComponent->SetPosition(10, 10);
	fpsComponent->SetFont(font);
	scene.Add(fpsGo);


	//new peter pepper
	auto peterPepperGo = std::make_shared<dae::GameObject>();
	PeterPepper* peterComp = peterPepperGo->AddComponent<PeterPepper>();
	peterComp->Init();
	peterPepperGo->SetPosition(300, 540);

	//pepper
	auto pepperGo = peterPepperGo->AddChild();
	pepperGo->SetFollowParent(false);
	pepperGo->SetPosition(-1000, -1000);
	dae::Pepper* pepperComp = pepperGo->AddComponent<dae::Pepper>();
	pepperComp->Init();

	scene.Add(peterPepperGo);


	input.AddCommand(dae::ControllerButton::DpadUp, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveUp>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadDown, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveDown>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadLeft, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveLeft>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadRight, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveRight>(peterPepperGo)), 0);



	//UI
	auto UiPeter = std::make_shared<dae::GameObject>();
	dae::PlayerUiComponent* peterUiComp = UiPeter->AddComponent<dae::PlayerUiComponent>();
	peterUiComp->SetFont(font);
	peterUiComp->SetLives(peterComp->GetHealth()->GetHealth());
	peterUiComp->SetLives(3);
	peterUiComp->SetPosition(450, 10);
	scene.Add(UiPeter);
	peterComp->GetHealth()->addObserver(peterUiComp);

	//peterCommand
	input.AddCommand(dae::ControllerButton::ButtonA, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<PepperCommand>(peterPepperGo.get())), 0);


	std::unique_ptr<BunDropped> scorePeterCommand = std::make_unique<BunDropped>(peterPepperGo.get());
	scorePeterCommand->addObserver(peterUiComp);
	input.AddCommand(dae::ControllerButton::ButtonY, dae::ButtonActivateState::OnButtonRelease, std::move(scorePeterCommand), 0);

	input.AddCommand(dae::ControllerButton::DpadUp, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleUp>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadDown, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleForward>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadLeft, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleForward>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadRight, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleForward>(peterPepperGo)), 0);



	//second player
	
	/*
	//sally salt
	auto sallySaltGo = std::make_shared<dae::GameObject>();
	PeterPepper* sallyComp = sallySaltGo->AddComponent<PeterPepper>();
	scene.Add(sallySaltGo);


	//UI
	auto UiSally = std::make_shared<dae::GameObject>();
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
	///


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
		auto levelFloor = std::make_shared<dae::GameObject>();
		dae::CollisionBox* floor1 = levelFloor->AddComponent<dae::CollisionBox>();
		floor1->SetTag("floor");
		floor1->SetPosition(5, 565);
		floor1->SetBox(613, floorWidth);

		dae::CollisionBox* floor2 = levelFloor->AddComponent<dae::CollisionBox>();
		floor2->SetTag("floor");
		floor2->SetPosition(5, 469);
		floor2->SetBox(470, floorWidth);

		dae::CollisionBox* floor3 = levelFloor->AddComponent<dae::CollisionBox>();
		floor3->SetTag("floor");
		floor3->SetPosition(438, 420);
		floor3->SetBox(180, floorWidth);

		dae::CollisionBox* floor4 = levelFloor->AddComponent<dae::CollisionBox>();
		floor4->SetTag("floor");
		floor4->SetPosition(150, 373);
		floor4->SetBox(325, floorWidth);

		dae::CollisionBox* floor5 = levelFloor->AddComponent<dae::CollisionBox>();
		floor5->SetTag("floor");
		floor5->SetPosition(5, 325);
		floor5->SetBox(180, floorWidth);


		dae::CollisionBox* floor6 = levelFloor->AddComponent<dae::CollisionBox>();
		floor6->SetTag("floor");
		floor6->SetPosition(438, 325);
		floor6->SetBox(180, floorWidth);

		dae::CollisionBox* floor7 = levelFloor->AddComponent<dae::CollisionBox>();
		floor7->SetTag("floor");
		floor7->SetPosition(150, 277);
		floor7->SetBox(180, floorWidth);

		dae::CollisionBox* floor8 = levelFloor->AddComponent<dae::CollisionBox>();
		floor8->SetTag("floor");
		floor8->SetPosition(5, 230);
		floor8->SetBox(180, floorWidth);

		dae::CollisionBox* floor9 = levelFloor->AddComponent<dae::CollisionBox>();
		floor9->SetTag("floor");
		floor9->SetPosition(292, 230);
		floor9->SetBox(325, floorWidth);

		dae::CollisionBox* floor10 = levelFloor->AddComponent<dae::CollisionBox>();
		floor10->SetTag("floor");
		floor10->SetPosition(5, 133);
		floor10->SetBox(613, floorWidth);

		scene.Add(levelFloor);

	}

	//LEVEL LADDERS
	{
		//testLadder
		int ladderWidth = 10;
		auto ladderGO = std::make_shared<dae::GameObject>();
		dae::CollisionBox* ladder1 = ladderGO->AddComponent<dae::CollisionBox>();
		ladder1->SetTag("Ladder");
		ladder1->SetPosition(18, 300);
		ladder1->SetBox(ladderWidth, 271);

		dae::CollisionBox* ladder2 = ladderGO->AddComponent<dae::CollisionBox>();
		ladder2->SetTag("Ladder");
		ladder2->SetPosition(18, 108);
		ladder2->SetBox(ladderWidth, 130);

		dae::CollisionBox* ladder3 = ladderGO->AddComponent<dae::CollisionBox>();
		ladder3->SetTag("Ladder");
		ladder3->SetPosition(90, 205);
		ladder3->SetBox(ladderWidth, 271);

		dae::CollisionBox* ladder4 = ladderGO->AddComponent<dae::CollisionBox>();
		ladder4->SetTag("Ladder");
		ladder4->SetPosition(164, 109);
		ladder4->SetBox(ladderWidth, 462);

		dae::CollisionBox* ladder5 = ladderGO->AddComponent<dae::CollisionBox>();
		ladder5->SetTag("Ladder");
		ladder5->SetPosition(235, 109);
		ladder5->SetBox(ladderWidth, 176);

		dae::CollisionBox* ladder6 = ladderGO->AddComponent<dae::CollisionBox>();
		ladder6->SetTag("Ladder");
		ladder6->SetPosition(307, 109);
		ladder6->SetBox(ladderWidth, 462);

		dae::CollisionBox* ladder7 = ladderGO->AddComponent<dae::CollisionBox>();
		ladder7->SetTag("Ladder");
		ladder7->SetPosition(380, 205);
		ladder7->SetBox(ladderWidth, 176);

		dae::CollisionBox* ladder8 = ladderGO->AddComponent<dae::CollisionBox>();
		ladder8->SetTag("Ladder");
		ladder8->SetPosition(450, 109);
		ladder8->SetBox(ladderWidth, 462);

		dae::CollisionBox* ladder9 = ladderGO->AddComponent<dae::CollisionBox>();
		ladder9->SetTag("Ladder");
		ladder9->SetPosition(523, 300);
		ladder9->SetBox(ladderWidth, 271);

		dae::CollisionBox* ladder10 = ladderGO->AddComponent<dae::CollisionBox>();
		ladder10->SetTag("Ladder");
		ladder10->SetPosition(595, 396);
		ladder10->SetBox(ladderWidth, 175);

		dae::CollisionBox* ladder11 = ladderGO->AddComponent<dae::CollisionBox>();
		ladder11->SetTag("Ladder");
		ladder11->SetPosition(595, 109);
		ladder11->SetBox(ladderWidth, 222);

		scene.Add(ladderGO);
	}

	//first burger
	{
		//add burgers
		auto topBunGo = std::make_shared<dae::GameObject>();
		topBunGo->SetPosition(50, 210);
		dae::Ingredient* topBun = topBunGo->AddComponent<dae::Ingredient>();
		topBun->Init("bun.png");
		scene.Add(topBunGo);

		auto midBunGo = std::make_shared<dae::GameObject>();
		midBunGo->SetPosition(50, 290);
		dae::Ingredient* midBun = midBunGo->AddComponent<dae::Ingredient>();
		midBun->Init("salad.png");
		scene.Add(midBunGo);

		auto mid2BunGo = std::make_shared<dae::GameObject>();
		mid2BunGo->SetPosition(50, 430);
		dae::Ingredient* mid2Bun = mid2BunGo->AddComponent<dae::Ingredient>();
		mid2Bun->Init("patty.png");
		scene.Add(mid2BunGo);

		auto botBunGo = std::make_shared<dae::GameObject>();
		botBunGo->SetPosition(50, 530);
		dae::Ingredient* botBun = botBunGo->AddComponent<dae::Ingredient>();
		botBun->Init("bun_Bottom.png");
		scene.Add(botBunGo);

		//ADDING TESTPLATE
		auto plate1 = std::make_shared<dae::GameObject>();
		dae::CollisionBox* floor6 = plate1->AddComponent<dae::CollisionBox>();
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
	auto enemyGO = std::make_shared<dae::GameObject>();
	dae::Enemy* enemy = enemyGO->AddComponent<dae::Enemy>();

	dae::AnimationManager* BeanAnimationComp = enemyGO->AddComponent<dae::AnimationManager>();
	BeanAnimationComp->AddAnimation("Bean_Up.png", "up", 64, 32, 2, 1, 0.5f);
	BeanAnimationComp->AddAnimation("Bean_Down.png", "down", 64, 32, 2, 1, 0.5f);
	BeanAnimationComp->AddAnimation("Bean_Left.png", "left", 64, 32, 2, 1, 0.5f);
	BeanAnimationComp->AddAnimation("Bean_Right.png", "right", 64, 32, 2, 1, 0.5f);
	BeanAnimationComp->AddAnimation("Bean_Death.png", "death", 128, 32, 4, 1, 0.5f);
	BeanAnimationComp->AddAnimation("Bean_Stunned.png", "stunned", 64, 32, 2, 1, 0.25f);
	BeanAnimationComp->SetActiveAnimation("down");

	enemy->Init(BeanAnimationComp, glm::vec2(0,540), 2.f);
	enemy->AddPlayer(peterComp);
	scene.Add(enemyGO);


}


