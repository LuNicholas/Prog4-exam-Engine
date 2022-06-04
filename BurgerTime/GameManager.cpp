#include "BurgerTimePCH.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Events.h"
#include "Plate.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "PeterPepper.h"


GameManager::GameManager()
	:m_GamePaused(false)
	, m_PlayerAmount(0)
	, m_DoOnce(false)
	, m_pLevel(nullptr)
	, m_NextLevel(false)
	, m_PauseTime(2.0f)
	, m_PauseTimer(0.f)
{
}
GameManager::~GameManager()
{
}


void GameManager::AddEnemy(dae::Enemy* enemy)
{
	m_Enemies.push_back(enemy);
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
			m_pPlayers.at(i)->GetComponent<PeterPepper>()->SetSpawn(glm::vec2(spawnPoint.x, spawnPoint.y));
			m_pPlayers.at(i)->SetPosition(spawnPoint.x, spawnPoint.y);
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
				dae::SceneManager::GetInstance().NextScene();
				FullReset();
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
	m_DoOnce = false;
	m_PauseTimer = 0;

	//RESET ENEMIES 

	//reset imgrediemts
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

	}
}
