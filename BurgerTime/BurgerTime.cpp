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
#include "Highscores.h"


std::vector<std::shared_ptr<dae::GameObject>> CreateCharacters();
void Level1(std::vector<std::shared_ptr<dae::GameObject>>& players);
void Level2(std::vector<std::shared_ptr<dae::GameObject>>& players);
void Level3(std::vector<std::shared_ptr<dae::GameObject>>& players);
void Highscore(std::vector<std::shared_ptr<dae::GameObject>>& players);
ButtonManager* MainMenu();

int main(int, char* [])
{
	dae::Minigin engine;
	engine.Initialize();
	dae::ResourceManager::GetInstance().Init("../Data/");///////COMMENTED SHIT IN MINIGIN THISH THISH 

	dae::SceneManager::GetInstance().CreateScene("mainMenu");
	dae::SceneManager::GetInstance().CreateScene("level1");
	dae::SceneManager::GetInstance().CreateScene("level2");
	dae::SceneManager::GetInstance().CreateScene("level3");
	dae::SceneManager::GetInstance().CreateScene("highscore");



	auto players = CreateCharacters();
	auto buttonManager = MainMenu();


	dae::InputManager::GetInstance().AddCommand(dae::ControllerButton::ButtonX, dae::ButtonActivateState::OnButtonDown
		, std::move(std::make_unique<NextScene>(buttonManager, players.at(0)->GetComponent<PeterPepper>(), players.at(1)->GetComponent<PeterPepper>())), 0);

	Level1(players);
	Level2(players);
	Level3(players);
	Highscore(players);

	dae::SceneManager::GetInstance().SetActiveScene("mainMenu");

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
	peterComp->Init(glm::vec2(300, 540), 1, 5);
	playerGOs.push_back(peterPepperGo);

	//pepper
	auto pepperGo = peterPepperGo->AddChild();
	pepperGo->SetFollowParent(false);
	pepperGo->SetPosition(-1000, -1000);
	pepperGo->AddComponent<dae::Pepper>()->Init();

	//CONSOLECOMMANDS
	input.AddCommand(dae::ControllerButton::DpadUp, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveUp>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadDown, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveDown>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadLeft, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveLeft>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadRight, dae::ButtonActivateState::IsPressed, std::move(std::make_unique<MoveRight>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::ButtonA, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<PepperCommand>(peterPepperGo.get())), 0);
	input.AddCommand(dae::ControllerButton::DpadUp, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleUp>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadDown, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleForward>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadLeft, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleForward>(peterPepperGo)), 0);
	input.AddCommand(dae::ControllerButton::DpadRight, dae::ButtonActivateState::OnButtonRelease, std::move(std::make_unique<IdleForward>(peterPepperGo)), 0);

	//KEYBOARDCOMMANDS
	input.AddCommand(SDL_SCANCODE_W, dae::InputManager::KeyboardButtonActivateState::pressed, std::move(std::make_unique<MoveUp>(peterPepperGo)));
	input.AddCommand(SDL_SCANCODE_S, dae::InputManager::KeyboardButtonActivateState::pressed, std::move(std::make_unique<MoveDown>(peterPepperGo)));
	input.AddCommand(SDL_SCANCODE_A, dae::InputManager::KeyboardButtonActivateState::pressed, std::move(std::make_unique<MoveLeft>(peterPepperGo)));
	input.AddCommand(SDL_SCANCODE_D, dae::InputManager::KeyboardButtonActivateState::pressed, std::move(std::make_unique<MoveRight>(peterPepperGo)));
	input.AddCommand(SDL_SCANCODE_R, dae::InputManager::KeyboardButtonActivateState::release, std::move(std::make_unique<PepperCommand>(peterPepperGo.get())));
	input.AddCommand(SDL_SCANCODE_W, dae::InputManager::KeyboardButtonActivateState::release, std::move(std::make_unique<IdleUp>(peterPepperGo)));
	input.AddCommand(SDL_SCANCODE_S, dae::InputManager::KeyboardButtonActivateState::release, std::move(std::make_unique<IdleForward>(peterPepperGo)));
	input.AddCommand(SDL_SCANCODE_A, dae::InputManager::KeyboardButtonActivateState::release, std::move(std::make_unique<IdleForward>(peterPepperGo)));
	input.AddCommand(SDL_SCANCODE_D, dae::InputManager::KeyboardButtonActivateState::release, std::move(std::make_unique<IdleForward>(peterPepperGo)));



	//UI
	auto UiPeter = peterPepperGo->AddChild();
	UiPeter->SetFollowParent(false);
	dae::PlayerUiComponent* peterUiComp = UiPeter->AddComponent<dae::PlayerUiComponent>();
	peterUiComp->SetFont(font);
	peterUiComp->SetLives(peterComp->GetHealth()->GetHealth());
	peterUiComp->SetPosition(450, 10);

	dae::Texture2DComponent* livesTexture = UiPeter->AddComponent<dae::Texture2DComponent>();
	livesTexture->SetTexture("PeterPepper/Peter_Lives.png");
	livesTexture->SetPosition(435, 18);

	dae::Texture2DComponent* pepperTexture = UiPeter->AddComponent<dae::Texture2DComponent>();
	pepperTexture->SetTexture("PeterPepper/Peter_Pepper.png");
	pepperTexture->SetPosition(380, 18);


	
	//second player
	auto sallySaltGo = std::make_shared<dae::GameObject>();
	PeterPepper* sallyComp = sallySaltGo->AddComponent<PeterPepper>();
	sallyComp->Init(glm::vec2(350, 540), 1, 5);
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
	sallyUiComp->SetLives(sallyComp->GetHealth()->GetHealth());
	sallyUiComp->SetPosition(450, 40);
	sallyUiComp->SetScoreVisible(false);

	dae::Texture2DComponent* livesTextureSally = UiSally->AddComponent<dae::Texture2DComponent>();
	livesTextureSally->SetTexture("PeterPepper/Peter_Lives.png");
	livesTextureSally->SetPosition(435, 48);

	dae::Texture2DComponent* pepperTextureSally = UiSally->AddComponent<dae::Texture2DComponent>();
	pepperTextureSally->SetTexture("PeterPepper/Peter_Pepper.png");
	pepperTextureSally->SetPosition(380, 48);



	return playerGOs;
}

void Level1(std::vector<std::shared_ptr<dae::GameObject>>& players)
{
	auto& scene = dae::SceneManager::GetInstance().GetScene("level1");
	auto& input = dae::InputManager::GetInstance();

	//fps game object
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fpsGo = std::make_shared<dae::GameObject>();
	dae::FpsComponent* fpsComponent = fpsGo->AddComponent<dae::FpsComponent>();
	fpsComponent->SetPosition(10, 10);
	fpsComponent->SetFont(font);
	scene.Add(fpsGo);


	//levelsprite
	auto levelGO = std::make_shared<dae::GameObject>();
	dae::Texture2DComponent* levelTexture = levelGO->AddComponent<dae::Texture2DComponent>();
	levelTexture->SetTexture("Level/level1.png");
	levelTexture->SetPosition(0, 700 - 600);
	scene.Add(levelGO);



	//SOUND
#if _DEBUG
	SoundServiceLocator::RegisterSoundSystem(new LoggingSoundSystem(new SDLSoundSystem()));
#else
	SoundServiceLocator::RegisterSoundSystem(new SDLSoundSystem());
#endif // _DEBUG
	SoundServiceLocator::GetSoundSystem().RegisterSound(0, "../Data/meow1.wav");
	std::unique_ptr<PlaySound> playMeow = std::make_unique<PlaySound>(0);
	input.AddCommand(dae::ControllerButton::ButtonB, dae::ButtonActivateState::OnButtonRelease, std::move(playMeow), 0);





	//add level
	LevelReader levelReader;
	auto level = std::make_shared<dae::GameObject>();
	levelReader.AddLevel("../Data/Level/level1test.txt", level);
	level->SetPosition(-1000, -1000);
	scene.Add(level);

	auto gameManagerGo = std::make_shared<dae::GameObject>();
	GameManager* gameManagerComp = gameManagerGo->AddComponent<GameManager>();
	players.at(0)->GetComponent<PeterPepper>()->addObserver(gameManagerComp);
	players.at(1)->GetComponent<PeterPepper>()->addObserver(gameManagerComp);


	
	//GETTING INGREDIENTS
	auto ingredients = levelReader.GetIngredients();
	for (auto ingredient : ingredients)
	{
		scene.Add(ingredient);
		ingredient->GetComponent<dae::Ingredient>()->addObserver(players.at(0)->GetChildAt(1)->GetComponent<dae::PlayerUiComponent>());
		//ingredient->GetComponent<dae::Ingredient>()->addObserver(players.at(1)->GetChildAt(1)->GetComponent<dae::PlayerUiComponent>());
		gameManagerComp->AddIngredient(ingredient->GetComponent<dae::Ingredient>());
		ingredient->SetPosition(-1000, -1000);
	}

	//GETTING PLATES
	auto plates = levelReader.GetPlates();
	for (auto plate : plates)
	{
		scene.Add(plate);
		gameManagerComp->AddPlate(plate->GetComponent<Plate>());
		plate->SetPosition(-1000, -1000);
	}



	//enemy test
	auto enemyGO = std::make_shared<dae::GameObject>();
	dae::Enemy* enemy = enemyGO->AddComponent<dae::Enemy>();
	enemy->Init(dae::EnemyType::bean, glm::vec2(0, 540), 2.f);
	enemy->AddPlayer(players.at(0)->GetComponent<PeterPepper>());
	enemy->AddPlayer(players.at(1)->GetComponent<PeterPepper>());
	scene.Add(enemyGO);




	//adding enemies
	gameManagerComp->AddEnemy(enemy);
	//adding level
	gameManagerComp->SetLevel(level);
	//adding player
	gameManagerComp->AddPlayer(players.at(0), glm::vec2(300, 540));
	gameManagerComp->AddPlayer(players.at(1), glm::vec2(325, 540));

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

	//fps game object
	auto fpsGo = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	dae::FpsComponent* fpsComponent = fpsGo->AddComponent<dae::FpsComponent>();
	fpsComponent->SetPosition(10, 10);
	fpsComponent->SetFont(font);
	scene.Add(fpsGo);

	//level
	auto levelGO = std::make_shared<dae::GameObject>();
	dae::Texture2DComponent* levelTexture = levelGO->AddComponent<dae::Texture2DComponent>();
	levelTexture->SetTexture("Level/level2.png");
	levelTexture->SetPosition(0, 700 - 600);
	scene.Add(levelGO);



	LevelReader levelReader;
	auto level = std::make_shared<dae::GameObject>();
	levelReader.AddLevel("../Data/Level/level2test.txt", level);
	level->SetPosition(-2000, -2000);
	scene.Add(level);

	auto gameManagerGo = std::make_shared<dae::GameObject>();
	GameManager* gameManagerComp = gameManagerGo->AddComponent<GameManager>();
	players.at(0)->GetComponent<PeterPepper>()->addObserver(gameManagerComp);
	players.at(1)->GetComponent<PeterPepper>()->addObserver(gameManagerComp);



	//adding level to gameManager
	gameManagerComp->SetLevel(level);



	auto ingredients = levelReader.GetIngredients();
	for (auto ingredient : ingredients)
	{
		scene.Add(ingredient);
		ingredient->GetComponent<dae::Ingredient>()->addObserver(players.at(0)->GetChildAt(1)->GetComponent<dae::PlayerUiComponent>());
		ingredient->GetComponent<dae::Ingredient>()->addObserver(players.at(1)->GetChildAt(1)->GetComponent<dae::PlayerUiComponent>());
		gameManagerComp->AddIngredient(ingredient->GetComponent<dae::Ingredient>());
		ingredient->SetPosition(-1000, -1000);
	}

	//GETTING PLATES
	auto plates = levelReader.GetPlates();
	for (auto plate : plates)
	{
		scene.Add(plate);
		gameManagerComp->AddPlate(plate->GetComponent<Plate>());
		plate->SetPosition(-1000, -1000);
	}


	//adding enemies
	//gameManagerComp->AddEnemy(enemy);



	//adding player
	gameManagerComp->AddPlayer(players.at(0), glm::vec2(298, 493));
	gameManagerComp->AddPlayer(players.at(1), glm::vec2(310, 493));

	scene.Add(gameManagerGo);


	for (auto& player : players)
	{
		scene.Add(player);
	}
}

void Level3(std::vector<std::shared_ptr<dae::GameObject>>& players)
{
	auto& scene = dae::SceneManager::GetInstance().GetScene("level3");
	auto& input = dae::InputManager::GetInstance();

	//fps game object
	auto fpsGo = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	dae::FpsComponent* fpsComponent = fpsGo->AddComponent<dae::FpsComponent>();
	fpsComponent->SetPosition(10, 10);
	fpsComponent->SetFont(font);
	scene.Add(fpsGo);

	//LEVEL
	auto levelGO = std::make_shared<dae::GameObject>();
	dae::Texture2DComponent* levelTexture = levelGO->AddComponent<dae::Texture2DComponent>();
	levelTexture->SetTexture("Level/level3.png");
	levelTexture->SetPosition(0, 700 - 600);
	scene.Add(levelGO);

	LevelReader levelReader;
	auto level = std::make_shared<dae::GameObject>();
	levelReader.AddLevel("../Data/Level/level3test.txt", level);
	level->SetPosition(-2000, -2000);
	scene.Add(level);


	auto gameManagerGo = std::make_shared<dae::GameObject>();
	GameManager* gameManagerComp = gameManagerGo->AddComponent<GameManager>();
	players.at(0)->GetComponent<PeterPepper>()->addObserver(gameManagerComp);
	players.at(1)->GetComponent<PeterPepper>()->addObserver(gameManagerComp);


	//adding level to gameManager
	gameManagerComp->SetLevel(level);



	auto ingredients = levelReader.GetIngredients();
	for (auto ingredient : ingredients)
	{
		scene.Add(ingredient);
		ingredient->GetComponent<dae::Ingredient>()->addObserver(players.at(0)->GetChildAt(1)->GetComponent<dae::PlayerUiComponent>());
		ingredient->GetComponent<dae::Ingredient>()->addObserver(players.at(1)->GetChildAt(1)->GetComponent<dae::PlayerUiComponent>());
		gameManagerComp->AddIngredient(ingredient->GetComponent<dae::Ingredient>());
		ingredient->SetPosition(-1000, -1000);
	}

	//GETTING PLATES
	auto plates = levelReader.GetPlates();
	for (auto plate : plates)
	{
		scene.Add(plate);
		gameManagerComp->AddPlate(plate->GetComponent<Plate>());
		plate->SetPosition(-1000, -1000);
	}


	//adding player
	gameManagerComp->AddPlayer(players.at(0), glm::vec2(298, 150));
	gameManagerComp->AddPlayer(players.at(1), glm::vec2(310, 150));

	scene.Add(gameManagerGo);


	for (auto& player : players)
	{
		scene.Add(player);
	}
}

void Highscore(std::vector<std::shared_ptr<dae::GameObject>>& players)
{
	auto& scene = dae::SceneManager::GetInstance().GetScene("highscore");
	auto& input = dae::InputManager::GetInstance();

	//levelsprite
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto levelGO = std::make_shared<dae::GameObject>();
	dae::Highscores* highScores= levelGO->AddComponent<dae::Highscores>();
	highScores->Init(players.at(0), font);
	scene.Add(levelGO);
}