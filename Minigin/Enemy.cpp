#include "MiniginPCH.h"
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
{


}
dae::Enemy::~Enemy()
{
}

void dae::Enemy::Init()
{
	CollisionBox* collider = m_pGameObject->AddComponent<CollisionBox>();
	collider->SetBox(32, 32);
	collider->SetTag("enemy");

	m_pMovementComp = m_pGameObject->AddComponent<MovementComponent>();
	m_pMovementComp->SetMovementBox(collider);
	m_pMovementComp->SetSpeed(0.5f);


	m_pAnimationComp = m_pGameObject->AddComponent<AnimationManager>();
	m_pAnimationComp->AddAnimation("Bean_Up.png", "up", 64, 32, 2, 1, 0.5f);
	m_pAnimationComp->AddAnimation("Bean_Down.png", "down", 64, 32, 2, 1, 0.5f);
	m_pAnimationComp->AddAnimation("Bean_Left.png", "left", 64, 32, 2, 1, 0.5f);
	m_pAnimationComp->AddAnimation("Bean_Right.png", "right", 64, 32, 2, 1, 0.5f);
	m_pAnimationComp->SetActiveAnimation("down");
}

void dae::Enemy::Update(float deltaTime)
{
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
				//m_pGameObject->GetComponent<dae::AnimationManager>()->SetActiveAnimation("right");
				break;
			}
		}
	}
}

void dae::Enemy::KillEnemy()
{
}





/*
	if (m_OnLadder)
	{
		if (m_GoingUp)
		{
			if (thisPos.y < playerPos.y - 5 || (thisPos.y > playerPos.y - 5 && thisPos.y < playerPos.y + 5))// player is lower while going up or same height
			{
				if (thisPos.x > playerPos.x)// go left
				{
					if (m_pMovementComp->MoveRight())
					{
						m_GoingUp = false;
						m_OnLadder = false;
						m_GoingRight = true;
					}
				}
				else if (thisPos.x < playerPos.x)
				{
					if (m_pMovementComp->MoveLeft())
					{
						m_GoingUp = false;
						m_OnLadder = false;
						m_GoingRight = false;
					}
				}

			}


			if (!m_pMovementComp->MoveUp())
				m_OnLadder = false;
		}
		else
		{
			if (!m_pMovementComp->MoveDown())
				m_OnLadder = false;
		}
	}
	else if (thisPos.y > playerPos.y + 5)//todo //not on ladder with player being higher
	{
		if (m_pMovementComp->MoveUp())
		{
			m_OnLadder = true;
			m_GoingUp = true;
		}
	}
	else if (thisPos.y < playerPos.y - 5)//todo //not on ladder with player being lower
	{
		if (m_pMovementComp->MoveDown())
		{
			m_OnLadder = true;
			m_GoingUp = false;
		}
	}


*/