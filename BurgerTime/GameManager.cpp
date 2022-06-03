#include "BurgerTimePCH.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Events.h"


GameManager::GameManager()
	:m_GamePaused(false)
	, m_PlayerAmount(0)
{
}
GameManager::~GameManager()
{
}


void GameManager::AddEnemy(dae::Enemy* enemy)
{
	m_Enemies.push_back(enemy);
}

void GameManager::Update(float deltaTime)
{
	if (!m_GamePaused)
		return;

	m_PauseTimer += deltaTime;
	if (m_PauseTimer >= m_PauseTime)
	{
		m_PauseTimer = 0;
		Reset();
		m_GamePaused = false;
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
	//RESET ENEMIES 
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
