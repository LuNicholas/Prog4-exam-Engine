#include "MiniginPCH.h"
#include "Enemy.h"
#include "GameObject.h"
#include "CollisionBox.h"
#include <algorithm>
#include "PeterPepper.h"

dae::Enemy::Enemy()
	:m_OnLadder(false)
	, m_GoingUp(false)
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
}

void dae::Enemy::Update(float deltaTime)
{
	glm::vec3 thisPos = m_Transform.GetPosition();

	CollisionBox* pCollider = m_pGameObject->GetComponent<CollisionBox>();
	std::vector<CollisionBox*> colldingBoxes = pCollider->GetCollidingWith();

	if (m_Players.size() == 1)
	{
		glm::vec3 playerPos = m_Players.front()->GetPosition();
		if (m_OnLadder)//GET OFF LADDER AT CORRECT TIME
		{
			if (m_GoingUp)
			{
				if (m_CurrentLadder->IsPointInCollider(glm::vec2(pCollider->GetPosition().x + pCollider->GetSize().x / 2, pCollider->GetPosition().y)))
				{
					glm::vec2 currentPos = m_pGameObject->GetWorldPosition();
					m_pGameObject->SetPosition(currentPos.x, currentPos.y - 2);
				}
			}
			else
			{
				if (m_CurrentLadder->IsPointInCollider(glm::vec2(pCollider->GetPosition().x + pCollider->GetSize().x / 2, pCollider->GetPosition().y + pCollider->GetSize().y - 5)))
				{
					glm::vec2 currentPos = m_pGameObject->GetWorldPosition();
					m_pGameObject->SetPosition(currentPos.x, currentPos.y + 2);
				}
			}
		}
		else if (thisPos.y > playerPos.y)
		{
			for (dae::CollisionBox* pColliding : colldingBoxes)
			{
				if (pColliding->GetTag() == "Ladder")
				{
					if (pColliding->IsPointInCollider(glm::vec2(pCollider->GetPosition().x + pCollider->GetSize().x / 2, pCollider->GetPosition().y + pCollider->GetSize().y - 5)))
					{
						m_CurrentLadder = pColliding;
						m_OnLadder = true;
						m_GoingUp = true;
					}
				}
			}

		}
		else if (thisPos.y < playerPos.y)
		{
			for (dae::CollisionBox* pColliding : colldingBoxes)
			{
				if (pColliding->GetTag() == "Ladder")
				{
					if (pColliding->IsPointInCollider(glm::vec2(pCollider->GetPosition().x + pCollider->GetSize().x / 2, pCollider->GetPosition().y + pCollider->GetSize().y - 5)))
					{
						m_CurrentLadder = pColliding;
						m_OnLadder = true;
						m_GoingUp = false;
					}
				}
			}
		}

		if(thisPos.x < playerPos.x)


	}
	else if (m_Players.size() == 2)
	{

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
void dae::Enemy::MoveUp()
{
}
void dae::Enemy::MoveDown()
{
}