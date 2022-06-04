#include "BurgerTimePCH.h"
#include "Enemy.h"
#include "GameObject.h"
#include "CollisionBox.h"
#include <algorithm>
#include "PeterPepper.h"
#include "MovementComponent.h"
#include "AnimationManager.h"

dae::Enemy::Enemy()
	:m_OnLadder(false)
	, m_GoingUp(false)
	, m_pMovementComp(nullptr)
	, m_GoingRight(false)
	, m_MovementState(MoveState::Right)
	, m_PlayerHeightOffset(4)
	, m_pLastLadder(nullptr)
	, m_pAnimationComp(nullptr)
	, m_IsDead(false)
	, m_IsStunnned(false)
	, m_StunTime(1.5f)
	, m_CurrentStunTime(0)
	, m_IsActive(false)
	, m_DeathTime(6.f)
	, m_Paused(false)
	, m_InitialSpawnTime(0)
	, m_SpawnTimer(0)
	, m_DissapearTime(1.0f)
{


}
dae::Enemy::~Enemy()
{
}

void dae::Enemy::Init(EnemyType enemyType, glm::vec2 spawnPoint, float initialSpawnTime)
{
	CollisionBox* collider = m_pGameObject->AddComponent<CollisionBox>();
	collider->SetBox(32, 32);
	collider->SetTag("enemy");

	m_pMovementComp = m_pGameObject->AddComponent<MovementComponent>();
	m_pMovementComp->SetMovementBox(collider);
	m_pMovementComp->SetSpeed(75.f);


	m_pGameObject->SetPosition(-1000, -1000);
	m_SpawnPoint = spawnPoint;

	m_InitialSpawnTime = initialSpawnTime;


	m_pAnimationComp = m_pGameObject->AddComponent<dae::AnimationManager>();


	switch (enemyType)
	{
	case dae::EnemyType::bean:
		m_pAnimationComp->AddAnimation("Bean_Up.png", "up", 64, 32, 2, 1, 0.5f);
		m_pAnimationComp->AddAnimation("Bean_Down.png", "down", 64, 32, 2, 1, 0.5f);
		m_pAnimationComp->AddAnimation("Bean_Left.png", "left", 64, 32, 2, 1, 0.5f);
		m_pAnimationComp->AddAnimation("Bean_Right.png", "right", 64, 32, 2, 1, 0.5f);
		m_pAnimationComp->AddAnimation("Bean_Death.png", "death", 128, 32, 4, 1, 0.5f);
		m_pAnimationComp->AddAnimation("Bean_Stunned.png", "stunned", 64, 32, 2, 1, 0.25f);
		m_pAnimationComp->SetActiveAnimation("down");
		break;
	case dae::EnemyType::egg:
		break;
	case dae::EnemyType::Pickle:
		break;
	default:
		break;
	}





}


void dae::Enemy::Update(float deltaTime)
{

	if (m_Paused)
	{
		m_pMovementComp->Idle();
		return;
	}

	if (!m_IsActive)
	{
		m_SpawnTimer += deltaTime;
		if (m_SpawnTimer >= m_InitialSpawnTime)
		{
			m_IsActive = true;
			m_SpawnTimer = 0;
			m_pGameObject->SetPosition(m_SpawnPoint.x, m_SpawnPoint.y);
		}
		else
		{
			return;
		}
	}
	if (m_IsDead)
	{
		m_pMovementComp->Idle();
		m_SpawnTimer += deltaTime;
		if (m_SpawnTimer >= m_DeathTime)
		{
			m_SpawnTimer = 0;
			m_IsDead = false;
			m_pGameObject->SetPosition(m_SpawnPoint.x, m_SpawnPoint.y);
		}
		else if (m_SpawnTimer >= m_DissapearTime)
		{
			m_pGameObject->SetPosition(-1000, -1000);
			return;
		}
		else
		{
			return;
		}
	}
	if (m_IsStunnned)
	{
		m_pMovementComp->Idle();
		m_pAnimationComp->SetActiveAnimation("stunned");
		m_CurrentStunTime += deltaTime;
		if (m_CurrentStunTime >= m_StunTime)
		{
			m_IsStunnned = false;
			m_CurrentStunTime = 0;
		}
		return;
	}






	glm::vec3 thisPos = m_Transform.GetPosition();

	CollisionBox* pCollider = m_pGameObject->GetComponent<CollisionBox>();
	std::vector<CollisionBox*> colldingBoxes = pCollider->GetCollidingWith();

	glm::vec3 playerPos;

	if (m_Players.at(1)->GetActive() == true)
	{
		//get closest of the 2 players
		bool isPlayer1Dead = m_Players.front()->GetGameObject()->GetComponent<PeterPepper>()->GetIsDead();
		bool isPlayer2Dead = m_Players.at(1)->GetGameObject()->GetComponent<PeterPepper>()->GetIsDead();

		if (!isPlayer1Dead && !isPlayer2Dead)
		{
			if (glm::distance(m_pGameObject->GetWorldPosition(), m_Players.front()->GetPosition()) < glm::distance(m_pGameObject->GetWorldPosition(), m_Players.at(1)->GetPosition()))
			{
				playerPos = m_Players.front()->GetPosition();
			}
			else
			{
				playerPos = m_Players.at(1)->GetPosition();
			}
		}
		else if (isPlayer2Dead)
		{
			playerPos = m_Players.front()->GetPosition();
		}
		else
		{
			playerPos = m_Players.at(1)->GetPosition();
		}


		//check overlap with player2
		if (m_Players.at(1)->GetGameObject()->GetComponent<CollisionBox>()->IsOverlappingWith(pCollider))
		{
			m_Players.at(1)->Kill();
		}

		//check overlap with player1
		if (m_Players.at(0)->GetGameObject()->GetComponent<CollisionBox>()->IsOverlappingWith(pCollider))
		{
			m_Players.at(0)->Kill();
		}
	}
	else 
	{
		playerPos = m_Players.front()->GetPosition();

		//check overlap with player1
		if (m_Players.at(0)->GetGameObject()->GetComponent<CollisionBox>()->IsOverlappingWith(pCollider))
		{
			m_Players.at(0)->Kill();
		}
	}

	if (m_OnLadder)
	{
		if (thisPos.y > playerPos.y - m_PlayerHeightOffset
			&& thisPos.y < playerPos.y + m_PlayerHeightOffset && m_pMovementComp->OnPlatform())//same height as player 
		{
			m_OnLadder = false;
			if ((thisPos.y > playerPos.y - m_PlayerHeightOffset && thisPos.y < playerPos.y + m_PlayerHeightOffset))//same height as player
			{
				if (thisPos.x < playerPos.x)
				{
					m_MovementState = dae::MoveState::Right;
				}
				else if (thisPos.x > playerPos.x)
				{
					m_MovementState = dae::MoveState::Left;
				}
			}
		}

		//if going up check if player is below and get off asap
		if (m_MovementState == MoveState::Up && thisPos.y < playerPos.y - m_PlayerHeightOffset)
		{
			if (m_pMovementComp->OnPlatform())
			{
				if (thisPos.x < playerPos.x)
				{
					m_MovementState = dae::MoveState::Right;
				}
				else if (thisPos.x > playerPos.x)
				{
					m_MovementState = dae::MoveState::Left;
				}
				m_OnLadder = false;
			}
		}

		//if going down check if player is above and get off asap
		if (m_MovementState == MoveState::Dowm && thisPos.y > playerPos.y - m_PlayerHeightOffset)
		{
			if (m_pMovementComp->OnPlatform())
			{
				if (thisPos.x < playerPos.x)
				{
					m_MovementState = dae::MoveState::Right;
				}
				else if (thisPos.x > playerPos.x)
				{
					m_MovementState = dae::MoveState::Left;
				}
				m_OnLadder = false;
			}
		}
	}
	else if (thisPos.y > playerPos.y - m_PlayerHeightOffset
		&& thisPos.y < playerPos.y + m_PlayerHeightOffset)// not on ladder and same height as player
	{
		if (thisPos.x < playerPos.x)
		{
			m_MovementState = dae::MoveState::Right;
		}
		else if (thisPos.x > playerPos.x)
		{
			m_MovementState = dae::MoveState::Left;
		}
	}
	else//not on ladder and not same height
	{
		//checking on ladder as well so enemy doesnt go up and down same ladder
		if (m_pMovementComp->TouchingLadder())
		{
			if (m_pLastLadder != m_pMovementComp->GetLastLadder() || m_pMovementComp->GetLastLadder() == nullptr)
			{
				if (thisPos.y > playerPos.y + m_PlayerHeightOffset)//player is above enemy 
				{
					if (m_pMovementComp->MoveUp())//can move up 
					{
						m_OnLadder = true;
						m_MovementState = dae::MoveState::Up;
						m_pLastLadder = m_pMovementComp->GetLastLadder();
					}
				}
				if (thisPos.y < playerPos.y - m_PlayerHeightOffset)//player below enemy
				{
					if (m_pMovementComp->MoveDown())//can move up 
					{
						m_OnLadder = true;
						m_MovementState = dae::MoveState::Dowm;
						m_pLastLadder = m_pMovementComp->GetLastLadder();
					}
				}

			}
		}
	}

	//moving
	switch (m_MovementState)
	{
	case dae::MoveState::Up:
		if (!m_pMovementComp->MoveUp())
		{
			if (thisPos.x < playerPos.x)
			{
				m_MovementState = dae::MoveState::Right;
			}
			else if (thisPos.x > playerPos.x)
			{
				m_MovementState = dae::MoveState::Left;
			}
		}
		else
		{
			m_pAnimationComp->SetActiveAnimation("up");
		}
		break;
	case dae::MoveState::Dowm:
		if (!m_pMovementComp->MoveDown())
		{
			if (thisPos.x < playerPos.x)// is player right of enemy 
			{
				m_MovementState = dae::MoveState::Right;
			}
			else // player is leftside
			{
				m_MovementState = dae::MoveState::Left;
			}
		}
		else
		{
			m_pAnimationComp->SetActiveAnimation("down");
		}
		break;
	case dae::MoveState::Left:
		if (!m_pMovementComp->MoveLeft())
		{
			if (thisPos.y > playerPos.y + m_PlayerHeightOffset)//player is above enemy 
			{
				m_MovementState = dae::MoveState::Up;
			}
			else //player is below enemy
			{
				m_MovementState = dae::MoveState::Dowm;
			}
		}
		else
		{
			m_pAnimationComp->SetActiveAnimation("left");
		}
		break;
	case dae::MoveState::Right:
		if (!m_pMovementComp->MoveRight())
		{
			if (thisPos.y > playerPos.y + m_PlayerHeightOffset)//player is above enemy 
			{
				m_MovementState = dae::MoveState::Up;
			}
			else //player is below enemy
			{
				m_MovementState = dae::MoveState::Dowm;
			}
		}
		else
		{
			m_pAnimationComp->SetActiveAnimation("right");
		}
		break;
	}
}
void dae::Enemy::FixedUpdate(float deltaTime)
{
}
void dae::Enemy::Render() const
{
}

void dae::Enemy::AddPlayer(PeterPepper* player)
{
	if (std::find(m_Players.begin(), m_Players.end(), player) == m_Players.end())
	{
		m_Players.push_back(player);
	}
}


void dae::Enemy::KillEnemy()
{
	m_pAnimationComp->SetActiveAnimation("death");
	m_IsDead = true;
	m_OnLadder = false;

	//cooldown before resetting and moving to other pos
	//move enemy to reset
}
void dae::Enemy::SetStunned()
{
	m_IsStunnned = true;
}
bool dae::Enemy::GetIsDead()
{
	return m_IsDead;
}

void dae::Enemy::Pause()
{
	m_Paused = true;
}
void dae::Enemy::Reset()
{
	m_Paused = false;
	m_IsActive = false;
	m_IsDead = false;
	m_SpawnTimer = 0;
	m_pGameObject->SetPosition(-1000, -1000);
}