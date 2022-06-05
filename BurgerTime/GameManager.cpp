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
#include "EnemyPlayer.h"


GameManager::GameManager()
	:m_GamePaused(false)
	, m_PlayerAmount(0)
	, m_DoOnce(false)
	, m_pLevel(nullptr)
	, m_NextLevel(false)
	, m_PauseTime(2.0f)
	, m_PauseTimer(0.f)
	, m_PlayersDead(0)
	, m_VsMode(false)
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
void GameManager::AddPlayer(std::shared_ptr<dae::GameObject>& player, const glm::vec2& playerSpawn)
{
	m_pPlayers.push_back(player);
	m_SpawnPoints.push_back(playerSpawn);
}
void GameManager::AddEnemyPlayer(EnemyPlayer* enemyPlayer, const glm::vec2& playerSpawn)
{
	m_pEnemyPlayer = enemyPlayer;
	m_EnemyPlayerSpawn = playerSpawn;
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

		if (m_VsMode)
		{
			m_pEnemyPlayer->GetGameObject()->SetPosition(m_EnemyPlayerSpawn.x, m_EnemyPlayerSpawn.y);
			m_pEnemyPlayer->SetSpawn(m_EnemyPlayerSpawn);
		}

		for (dae::Enemy* enemy : m_Enemies)
		{
			if (m_VsMode)
				enemy->SetActive(false);
			else
				enemy->SetActive(true);
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
				//m_pLevel->SetPosition(-1000, -1000);
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

	if (m_VsMode)
	{
		m_pEnemyPlayer->GetGameObject()->SetPosition(m_EnemyPlayerSpawn.x, m_EnemyPlayerSpawn.y);
		m_pEnemyPlayer->SetPaused(false);
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
	if (m_VsMode)
	{
		m_pEnemyPlayer->GetGameObject()->SetPosition(m_EnemyPlayerSpawn.x, m_EnemyPlayerSpawn.y);
		m_pEnemyPlayer->SetPaused(false);
		m_pEnemyPlayer->SetActive(false);
		m_VsMode = false;
	}
	//reset imgrediemts
	for (dae::Ingredient* ingredient : m_Ingredients)
	{
		ingredient->Reset();
		ingredient->SetlleStartPlatform();
	}

	//reset plates
	for (Plate* plate : m_Plates)
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
	m_pLevel->SetPosition(-1000, -1000);

	//for (dae::Enemy* enemy : m_Enemies)
	//{
	//	enemy->GetGameObject()->SetPosition(-1000, -1000);
	//}

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

		m_pEnemyPlayer->SetPaused(true);
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
			ResetPlayers();
			FullReset();
			MoveLevel();
			m_PlayersDead -= m_PlayerAmount;
			m_PlayerAmount = 0;
			dae::SceneManager::GetInstance().SetActiveScene("highscore");
		}
		break;
	}
	case Event::enemyPlayerActivated:
	{
		m_VsMode = true;
		break;
	}
	}
}
