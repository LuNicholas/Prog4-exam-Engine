#include "BurgerTimePCH.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Enemy.h"
#include "Events.h"


GameManager::GameManager()
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

void GameManager::onNotify(const dae::GameObject& go, const Event& event)
{
	switch (event)
	{
	case Event::PlayerHit:
	{
		m_GamePaused = true;
		Pause();
		break;
	}

	}
}