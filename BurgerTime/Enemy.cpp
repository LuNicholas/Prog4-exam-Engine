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
	, m_DeathTime(3.f)
{


}
dae::Enemy::~Enemy()
{
}

void dae::Enemy::Init(dae::AnimationManager* animComp, glm::vec2 spawnPoint, float initialSpawnTime)
{
	CollisionBox* collider = m_pGameObject->AddComponent<CollisionBox>();
	collider->SetBox(32, 32);
	collider->SetTag("enemy");

	m_pMovementComp = m_pGameObject->AddComponent<MovementComponent>();
	m_pMovementComp->SetMovementBox(collider);
	m_pMovementComp->SetSpeed(0.5f);

	m_pAnimationComp = animComp;

	m_pGameObject->SetPosition(spawnPoint.x, spawnPoint.y);
	m_SpawnPoint = spawnPoint;
}


void dae::Enemy::Update(float deltaTime)
{

	if (!m_IsActive)
	{
		m_SpawnTimer += deltaTime;
		if (m_SpawnTimer >= m_InitialSpawnTime)
		{
			m_IsActive = true;
			m_SpawnTimer = 0;
		}
		else
		{
			return;
		}
	}


	if (m_IsDead)
	{
		m_SpawnTimer += deltaTime;
		if (m_SpawnTimer >= m_DeathTime)
		{
			m_SpawnTimer = 0;
			m_IsDead = false;
			m_pGameObject->SetPosition(m_SpawnPoint.x, m_SpawnPoint.y);
		}
		else if (m_SpawnTimer >= 0.5f)
		{
			m_pGameObject->SetPosition(-1000, -1000);
		}
		else
		{
			return;
		}
	}


	if (m_IsStunnned)
	{
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
	if (m_Players.size() == 1)
	{
		playerPos = m_Players.front()->GetPosition();
	}
	else if (m_Players.size() == 2)
	{
		//get closest of the 2 players
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

void dae::Enemy::MoveLeft()
{
}
void dae::Enemy::MoveRight()
{
	dae::CollisionBox* pCollider = m_pGameObject->GetComponent<dae::CollisionBox>();

	auto collidingWith = pCollider->GetCollidingWith();

	for (dae::CollisionBox* pColliding : collidingWith)
	{
		if (pColliding->GetTag() == "floor")
		{

			if (pColliding->IsPointInCollider(glm::vec2(pCollider->GetPosition().x + pCollider->GetSize().x, pCollider->GetPosition().y + pCollider->GetSize().y)))
			{
				glm::vec3 currentPos = m_pGameObject->GetWorldPosition();
				currentPos.x += 1;
				currentPos.y = pColliding->GetPosition().y - pCollider->GetSize().y + 5;
				m_pGameObject->SetPosition(currentPos.x, currentPos.y);
				break;
			}
		}
	}
}

void dae::Enemy::KillEnemy()
{
	m_pAnimationComp->SetActiveAnimation("death");
	m_IsDead = true;


	//cooldown before resetting and moving to other pos
	//move enemy to reset
}
void dae::Enemy::SetStunned()
{
	//m_pAnimationComp->SetActiveAnimation("stunned");
	m_IsStunnned = true;
}
bool dae::Enemy::GetIsDead()
{
	return m_IsDead;
}