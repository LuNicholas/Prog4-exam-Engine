#include "BurgerTimePCH.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Events.h"
#include "Plate.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "PeterPepper.h"
#include "Ingredient.h"


GameManager::GameManager()
	:m_GamePaused(false)
	, m_PlayerAmount(0)
	, m_DoOnce(false)
	, m_pLevel(nullptr)
	, m_NextLevel(false)
	, m_PauseTime(2.0f)
	, m_PauseTimer(0.f)
	, m_PlayersDead(0)
{
}
GameManager::~GameManager()
{
}


void GameManager::AddEnemy(dae::Enemy* enemy)
{
	m_Enemies.push_back(enemy);
}
void GameManager::AddIngredient(dae::Ingredient* ingredient)
{
	m_Ingredients.push_back(ingredient);
}
void GameManager::AddPlate(Plate* plate)
{
	m_Plates.push_back(plate);
}
void GameManager::SetLevel(std::shared_ptr<dae::GameObject>& level)
{
	m_pLevel = level;
}
void GameManager::AddPlayer(std::shared_ptr<dae::GameObject>& player, glm::vec2 playerSpawn)
{
	m_pPlayers.push_back(player);
	m_SpawnPoints.push_back(playerSpawn);
}


void GameManager::Update(float deltaTime)
{

	if (!m_DoOnce)
	{
		m_DoOnce = true;
		m_pLevel->SetPosition(0, 0);

		for (size_t i = 0; i < m_pPlayers.size(); i++)
		{
			glm::vec2 spawnPoint = m_SpawnPoints.at(i);
			if (m_pPlayers.at(i)->GetComponent<PeterPepper>()->GetActive())
			{
				m_pPlayers.at(i)->GetComponent<PeterPepper>()->SetSpawn(glm::vec2(spawnPoint.x, spawnPoint.y));
				m_pPlayers.at(i)->SetPosition(spawnPoint.x, spawnPoint.y);
			}
		}

		for (dae::Ingredient* ingredient : m_Ingredients)
		{
			ingredient->Reset();
			ingredient->SetlleStartPlatform();
		}
		for (Plate* plate : m_Plates)
		{
			plate->Reset();
		}
	}



	if (m_GamePaused)
	{
		m_PauseTimer += deltaTime;
		if (m_PauseTimer >= m_PauseTime)
		{
			m_PauseTimer = 0;
			Reset();
			m_GamePaused = false;


			if (m_NextLevel)//GO TO NEXT LEVEL
			{
				m_pLevel->SetPosition(-1000, -1000);
				if (dae::SceneManager::GetInstance().GetCurrentScene().GetSceneName() == "level3")
				{
					dae::SceneManager::GetInstance().SetActiveScene("level1");
				}
				else
				{
					dae::SceneManager::GetInstance().NextScene();
				}
				FullReset();
				MoveLevel();
			}
		}
	}


	int ingredientOnPlate = 0;
	for (Plate* plate : m_Plates)
	{
		if (!plate->IsPlateDone())
		{
			return;
		}
		else
		{
			ingredientOnPlate++;
		}
	}
	if (ingredientOnPlate == m_Plates.size())
	{
		m_NextLevel = true;
		m_GamePaused = true;
		Pause();
	}


}
void GameManager::FixedUpdate(float deltaTime)
{
}
void GameManager::Render() const
{
}

void GameManager::Pause()
{
	for (dae::Enemy* enemy : m_Enemies)
	{
		enemy->Pause();
	}
}
void GameManager::Reset()
{
	for (dae::Enemy* enemy : m_Enemies)
	{
		enemy->Reset();
	}
}
void GameManager::FullReset()
{
	m_NextLevel = false;
	m_DoOnce = false;
	m_PauseTimer = 0;

	//reset enemies 
	for (dae::Enemy* enemy : m_Enemies)
	{
		enemy->Reset();
	}

	//reset imgrediemts
	for (dae::Ingredient* ingredient : m_Ingredients)
	{
		ingredient->Reset();
		ingredient->SetlleStartPlatform();
	}

	//reset plates
	for (Plate* plate: m_Plates)
	{
		plate->Reset();
	}
}
void GameManager::ResetPlayers()
{
	for (auto& player : m_pPlayers)
	{
		player->GetComponent<PeterPepper>()->Reset();
	}
}
void GameManager::MoveLevel()
{
	for (dae::Enemy* enemy : m_Enemies)
	{
		enemy->GetGameObject()->SetPosition(-1000,-1000);
	}

	//reset imgrediemts
	for (dae::Ingredient* ingredient : m_Ingredients)
	{
		ingredient->GetGameObject()->SetPosition(-1000, -1000);
	}

	//reset plates
	for (Plate* plate : m_Plates)
	{
		plate->GetGameObject()->SetPosition(-1000, -1000);
	}

	m_pLevel->SetPosition(-1000, -1000);
}

void GameManager::onNotify(const dae::GameObject& go, const Event& event)
{
	switch (event)
	{
	case Event::PlayerHit:
	{
		if (m_PlayerAmount < 2)
		{
			m_GamePaused = true;
			Pause();
		}
		break;
	}
	case Event::PlayerActivated:
	{
		m_PlayerAmount++;
		break;
	}
	case Event::playerDead:
	{
		m_PlayersDead++;
		if (m_PlayersDead == m_PlayerAmount)
		{
			FullReset();
			ResetPlayers();
			m_PlayersDead -= m_PlayerAmount;
			m_PlayerAmount = 0;
			dae::SceneManager::GetInstance().SetActiveScene("highscore");
		}
		break;
	}
	}
}
