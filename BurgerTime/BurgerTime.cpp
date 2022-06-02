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
#include "Plate.h"
#include "GameManager.h"
#include "ButtonManager.h"


void Level1();
void MainMenu();

int main(int, char* [])
{
	dae::Minigin engine;
	engine.Initialize();
	dae::ResourceManager::GetInstance().Init("../Data/");///////COMMENTED SHIT IN MINIGIN THISH THISH 

	//adding player to all scenes?????????? to preserve everything

	MainMenu();
	Level1();

	//dae::SceneManager::GetInstance().SetActiveScene("mainMenu");
	
	engine.Run();

	engine.Cleanup();
	return 0;
}

void MainMenu()
{

	auto& scene = dae::SceneManager::GetInstance().CreateScene("mainMenu");
	auto& input = dae::InputManager::GetInstance();

	//levelsprite
	auto levelGO = std::make_shared<dae::GameObject>();
	dae::Texture2DComponent* levelTexture = levelGO->AddComponent<dae::Texture2DComponent>();
	levelTexture->SetTexture("MainMenu.png");
	levelTexture->SetPosition(50, 100);
	scene.Add(levelGO);

	auto buttonsGo = std::make_shared<dae::GameObject>();
	ButtonManager* buttonManager = buttonsGo->AddComponent<ButtonManager>();
	buttonManager->AddButton(glm::vec2(225, 320), glm::vec2(135, 25));//1 Player
	buttonManager->AddButton(glm::vec2(224, 352), glm::vec2(150, 25));//2 Players
	buttonManager->AddButton(glm::vec2(270, 385), glm::vec2(43, 25));// VS
	scene.Add(buttonsGo);

	input.AddCommand(dae::ControllerButton::ButtonX, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<NextScene>()), 0);

	input.AddCommand(dae::ControllerButton::DpadUp, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<PreviousButton>(buttonManager)), 0);
	input.AddCommand(dae::ControllerButton::DpadDown, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<NextButton>(buttonManager)), 0);
}

void Level1()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("level1");
	dae::SceneManager::GetInstance().SetActiveScene("level1");
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
	peterComp->Init(glm::vec2(300, 540), 5);

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
	peterUiComp->SetLives(4);
	peterUiComp->SetLives(peterComp->GetHealth()->GetHealth());
	peterUiComp->SetPosition(450, 10);
	scene.Add(UiPeter);

	dae::Texture2DComponent* livesTexture = UiPeter->AddComponent<dae::Texture2DComponent>();
	livesTexture->SetTexture("Peter_Lives.png");
	livesTexture->SetPosition(435, 18);

	dae::Texture2DComponent* pepperTexture = UiPeter->AddComponent<dae::Texture2DComponent>();
	pepperTexture->SetTexture("Peter_Pepper.png");
	pepperTexture->SetPosition(380, 18);


	peterComp->addObserver(peterUiComp);

	//peterCommand
	input.AddCommand(dae::ControllerButton::ButtonA, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<PepperCommand>(peterPepperGo.get())), 0);

	input.AddCommand(dae::ControllerButton::DpadUp, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleUp>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadDown, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleForward>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadLeft, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleForward>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadRight, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleForward>(peterPepperGo)), 0);

	//second player
	
	
	//sally salt
	auto sallySaltGo = std::make_shared<dae::GameObject>();
	PeterPepper* sallyComp = sallySaltGo->AddComponent<PeterPepper>();
	scene.Add(sallySaltGo);


	//UI
	//auto UiSally = std::make_shared<dae::GameObject>();
	//PlayerUiComponent* sallyUiComp = UiSally->AddComponent<PlayerUiComponent>();
	//sallyUiComp->SetFont(font);
	//sallyUiComp->SetLives(sallyComp->GetHealth()->GetHealth());
	//sallyUiComp->SetLives(3);
	//sallyUiComp->SetPosition(10, 325);
	//scene.Add(UiSally);

	//sallyComp->GetHealth()->addObserver(sallyUiComp);

	//sallyCommand
	//std::unique_ptr<HitCommand> hitSallyCommand = std::make_unique<HitCommand>(sallySaltGo.get());
	//input.AddCommand(dae::ControllerButton::ButtonA, dae::ButtonActivateState::OnButtonRelease, std::move(hitSallyCommand), 1);

	//std::unique_ptr<BunDropped> scoreSallyCommand = std::make_unique<BunDropped>(sallySaltGo.get());
	//scoreSallyCommand->addObserver(sallyUiComp);
	//input.AddCommand(dae::ControllerButton::ButtonY, dae::ButtonActivateState::OnButtonRelease, std::move(scoreSallyCommand), 1);
	
	


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

	//ingredients
	{
		//first burger
		{
			//add burgers
			auto topBun0Go = std::make_shared<dae::GameObject>();
			topBun0Go->SetPosition(50, 210);
			dae::Ingredient* topBun0Comp = topBun0Go->AddComponent<dae::Ingredient>();
			topBun0Comp->Init("bun.png");
			scene.Add(topBun0Go);

			auto salad0Go = std::make_shared<dae::GameObject>();
			salad0Go->SetPosition(50, 290);
			dae::Ingredient* salad0Comp = salad0Go->AddComponent<dae::Ingredient>();
			salad0Comp->Init("salad.png");
			scene.Add(salad0Go);

			auto patty0Go = std::make_shared<dae::GameObject>();
			patty0Go->SetPosition(50, 430);
			dae::Ingredient* patty0Comp = patty0Go->AddComponent<dae::Ingredient>();
			patty0Comp->Init("patty.png");
			scene.Add(patty0Go);

			auto botBun0Go = std::make_shared<dae::GameObject>();
			botBun0Go->SetPosition(50, 530);
			dae::Ingredient* botBun0Comp = botBun0Go->AddComponent<dae::Ingredient>();
			botBun0Comp->Init("bun_Bottom.png");
			scene.Add(botBun0Go);

			//ADDING TESTPLATE
			auto plate0Go = std::make_shared<dae::GameObject>();
			Plate* plate0Comp = plate0Go->AddComponent<Plate>();
			plate0Comp->Init();
			plate0Comp->AddIngredient(topBun0Comp);
			plate0Comp->AddIngredient(salad0Comp);
			plate0Comp->AddIngredient(patty0Comp);
			plate0Comp->AddIngredient(botBun0Comp);
			plate0Go->SetPosition(38, 695);
			scene.Add(plate0Go);


			topBun0Comp->addObserver(peterUiComp);
			salad0Comp->addObserver(peterUiComp);
			patty0Comp->addObserver(peterUiComp);
			botBun0Comp->addObserver(peterUiComp);

			//gamestate where to set requirements for next stage
			//add the all the plates to the gamestate and check if theyre all finished
			//if theyre all finished go to next scene

		}
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


	auto gameManagerGo = std::make_shared<dae::GameObject>();
	GameManager* gameManagerComp = gameManagerGo->AddComponent<GameManager>();
	peterComp->addObserver(gameManagerComp);
	scene.Add(gameManagerGo);
	gameManagerComp->AddEnemy(enemy);

}


