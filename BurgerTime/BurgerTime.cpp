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
#include "LevelReader.h"


std::vector<std::shared_ptr<dae::GameObject>> CreateCharacters();
void Level1(std::vector<std::shared_ptr<dae::GameObject>>& players);
void Level2(std::vector<std::shared_ptr<dae::GameObject>>& players);
ButtonManager* MainMenu();

int main(int, char* [])
{
	dae::Minigin engine;
	engine.Initialize();
	dae::ResourceManager::GetInstance().Init("../Data/");///////COMMENTED SHIT IN MINIGIN THISH THISH 

	dae::SceneManager::GetInstance().CreateScene("mainMenu");
	dae::SceneManager::GetInstance().CreateScene("level1");
	dae::SceneManager::GetInstance().CreateScene("level2");


	auto buttonManager = MainMenu();
	auto players = CreateCharacters();


	dae::InputManager::GetInstance().AddCommand(dae::ControllerButton::ButtonX, dae::ButtonActivateState::OnButtonDown
		, std::move(std::make_unique<NextScene>(buttonManager, players.at(0)->GetComponent<PeterPepper>(), players.at(1)->GetComponent<PeterPepper>())), 0);

	Level1(players);
	Level2(players);


	dae::SceneManager::GetInstance().SetActiveScene("mainMenu");
	//dae::SceneManager::GetInstance().SetActiveScene("level1");
	//dae::SceneManager::GetInstance().SetActiveScene("level2");

	engine.Run();

	engine.Cleanup();
	return 0;
}

ButtonManager* MainMenu()
{

	auto& scene = dae::SceneManager::GetInstance().GetScene("mainMenu");
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

	input.AddCommand(dae::ControllerButton::DpadUp, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<PreviousButton>(buttonManager)), 0);
	input.AddCommand(dae::ControllerButton::DpadDown, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<NextButton>(buttonManager)), 0);

	return buttonManager;
}

std::vector<std::shared_ptr<dae::GameObject>> CreateCharacters()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto& input = dae::InputManager::GetInstance();

	std::vector<std::shared_ptr<dae::GameObject>> playerGOs;

	///PLAYER 1
	//new peter pepper
	auto peterPepperGo = std::make_shared<dae::GameObject>();

	PeterPepper* peterComp = peterPepperGo->AddComponent<PeterPepper>();
	peterComp->Init(glm::vec2(300, 540), 5);
	playerGOs.push_back(peterPepperGo);

	//pepper
	auto pepperGo = peterPepperGo->AddChild();
	pepperGo->SetFollowParent(false);
	pepperGo->SetPosition(-1000, -1000);
	pepperGo->AddComponent<dae::Pepper>()->Init();


	input.AddCommand(dae::ControllerButton::DpadUp, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveUp>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadDown, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveDown>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadLeft, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveLeft>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadRight, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveRight>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::ButtonA, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<PepperCommand>(peterPepperGo.get())), 0);
	input.AddCommand(dae::ControllerButton::DpadUp, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleUp>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadDown, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleForward>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadLeft, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleForward>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadRight, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleForward>(peterPepperGo)), 0);


	//UI
	auto UiPeter = peterPepperGo->AddChild();
	UiPeter->SetFollowParent(false);
	dae::PlayerUiComponent* peterUiComp = UiPeter->AddComponent<dae::PlayerUiComponent>();
	peterUiComp->SetFont(font);
	peterUiComp->SetLives(4);
	peterUiComp->SetLives(peterComp->GetHealth()->GetHealth());
	peterUiComp->SetPosition(450, 10);

	dae::Texture2DComponent* livesTexture = UiPeter->AddComponent<dae::Texture2DComponent>();
	livesTexture->SetTexture("Peter_Lives.png");
	livesTexture->SetPosition(435, 18);

	dae::Texture2DComponent* pepperTexture = UiPeter->AddComponent<dae::Texture2DComponent>();
	pepperTexture->SetTexture("Peter_Pepper.png");
	pepperTexture->SetPosition(380, 18);
	peterComp->addObserver(peterUiComp);


	//////////////////////
	//second player
	auto sallySaltGo = std::make_shared<dae::GameObject>();
	PeterPepper* sallyComp = sallySaltGo->AddComponent<PeterPepper>();
	sallyComp->Init(glm::vec2(350, 540), 5);
	playerGOs.push_back(sallySaltGo);


	//pepper
	auto sallyPepperGo = sallySaltGo->AddChild();
	sallyPepperGo->SetFollowParent(false);
	sallyPepperGo->SetPosition(-1000, -1000);
	sallyPepperGo->AddComponent<dae::Pepper>()->Init();

	input.AddCommand(dae::ControllerButton::DpadUp, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveUp>(sallySaltGo)), 1);
	input.AddCommand(dae::ControllerButton::DpadDown, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveDown>(sallySaltGo)), 1);
	input.AddCommand(dae::ControllerButton::DpadLeft, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveLeft>(sallySaltGo)), 1);
	input.AddCommand(dae::ControllerButton::DpadRight, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveRight>(sallySaltGo)), 1);
	input.AddCommand(dae::ControllerButton::ButtonA, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<PepperCommand>(sallySaltGo.get())), 1);
	input.AddCommand(dae::ControllerButton::DpadUp, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleUp>(sallySaltGo)), 1);
	input.AddCommand(dae::ControllerButton::DpadDown, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleForward>(sallySaltGo)), 1);
	input.AddCommand(dae::ControllerButton::DpadLeft, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleForward>(sallySaltGo)), 1);
	input.AddCommand(dae::ControllerButton::DpadRight, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleForward>(sallySaltGo)), 1);


	//UI
	auto UiSally = sallySaltGo->AddChild();
	UiSally->SetFollowParent(false);
	dae::PlayerUiComponent* sallyUiComp = UiSally->AddComponent<dae::PlayerUiComponent>();
	sallyUiComp->SetFont(font);
	sallyUiComp->SetLives(4);
	sallyUiComp->SetLives(sallyComp->GetHealth()->GetHealth());
	sallyUiComp->SetPosition(450, 40);

	dae::Texture2DComponent* livesTextureSally = UiSally->AddComponent<dae::Texture2DComponent>();
	livesTextureSally->SetTexture("Peter_Lives.png");
	livesTextureSally->SetPosition(435, 48);

	dae::Texture2DComponent* pepperTextureSally = UiSally->AddComponent<dae::Texture2DComponent>();
	pepperTextureSally->SetTexture("Peter_Pepper.png");
	pepperTextureSally->SetPosition(380, 48);
	sallyComp->addObserver(sallyUiComp);



	return playerGOs;
}

void Level1(std::vector<std::shared_ptr<dae::GameObject>>& players)
{
	auto& scene = dae::SceneManager::GetInstance().GetScene("level1");
	auto& input = dae::InputManager::GetInstance();

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


	//add level
	LevelReader levelReader;
	auto level = std::make_shared<dae::GameObject>();
	levelReader.AddLevel("../Data/level1.txt", level);
	level->SetPosition(-1000, -1000);
	scene.Add(level);


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

	topBun0Comp->addObserver(players.at(0)->GetChildAt(1)->GetComponent<dae::PlayerUiComponent>());
	salad0Comp->addObserver(players.at(0)->GetChildAt(1)->GetComponent<dae::PlayerUiComponent>());
	patty0Comp->addObserver(players.at(0)->GetChildAt(1)->GetComponent<dae::PlayerUiComponent>());
	botBun0Comp->addObserver(players.at(0)->GetChildAt(1)->GetComponent<dae::PlayerUiComponent>());



	//enemy test
	auto enemyGO = std::make_shared<dae::GameObject>();
	dae::Enemy* enemy = enemyGO->AddComponent<dae::Enemy>();
	enemy->Init(dae::EnemyType::bean, glm::vec2(0, 540), 2.f);
	enemy->AddPlayer(players.at(0)->GetComponent<PeterPepper>());
	enemy->AddPlayer(players.at(1)->GetComponent<PeterPepper>());
	scene.Add(enemyGO);





	auto gameManagerGo = std::make_shared<dae::GameObject>();
	GameManager* gameManagerComp = gameManagerGo->AddComponent<GameManager>();
	players.at(1)->GetComponent<PeterPepper>()->addObserver(gameManagerComp);
	players.at(0)->GetComponent<PeterPepper>()->addObserver(gameManagerComp);

	//adding enemies
	gameManagerComp->AddEnemy(enemy);

	//adding ingredients
	gameManagerComp->AddPlate(plate0Comp);

	//adding level
	gameManagerComp->SetLevel(level);

	//adding player
	gameManagerComp->AddPlayer(players.at(0), glm::vec2(300, 540));

	scene.Add(gameManagerGo);


	for (auto& player : players)
	{
		scene.Add(player);
	}

}

void Level2(std::vector<std::shared_ptr<dae::GameObject>>& players)
{
	auto& scene = dae::SceneManager::GetInstance().GetScene("level2");
	auto& input = dae::InputManager::GetInstance();

	auto levelGO = std::make_shared<dae::GameObject>();
	dae::Texture2DComponent* levelTexture = levelGO->AddComponent<dae::Texture2DComponent>();
	levelTexture->SetTexture("level2.png");
	levelTexture->SetPosition(0, 700 - 600);
	scene.Add(levelGO);

	LevelReader levelReader;
	auto level = std::make_shared<dae::GameObject>();
	levelReader.AddLevel("../Data/level2.txt", level);
	level->SetPosition(-1000, -1000);
	scene.Add(level);


	//players.at(0)->SetPosition(298, 493);



	auto gameManagerGo = std::make_shared<dae::GameObject>();
	GameManager* gameManagerComp = gameManagerGo->AddComponent<GameManager>();
	//players.at(1)->GetComponent<PeterPepper>()->addObserver(gameManagerComp);
	players.at(0)->GetComponent<PeterPepper>()->addObserver(gameManagerComp);

	//adding enemies
	//gameManagerComp->AddEnemy(enemy);

	//adding ingredients
	//gameManagerComp->AddPlate(plate0Comp);

	//adding level
	gameManagerComp->SetLevel(level);

	//adding player
	gameManagerComp->AddPlayer(players.at(0), glm::vec2(298, 493));

	scene.Add(gameManagerGo);


	for (auto& player : players)
	{
		scene.Add(player);
	}
}