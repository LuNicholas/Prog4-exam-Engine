#include "MiniginPCH.h"
#include "PeterPepper.h"
#include "GameObject.h"
#include "CollisionBox.h"
#include "AnimationManager.h"

dae::PeterPepper::PeterPepper()
	:m_MoveSpeed(10)
{
	m_pHealth = new dae::Health(3);
}
dae::PeterPepper::~PeterPepper()
{
	delete m_pHealth;
}

void dae::PeterPepper::Update(float deltaTime)
{
	//CollisionBox* collision = m_pGameObject->GetComponent<CollisionBox>();
	//if (collision != nullptr)
	//{
	//	auto test = collision->GetCollidingWith();
	//	if (test.size() > 0)
	//	{
	//		std::cout << "im collidng \n";
	//	}
	//}
}
void dae::PeterPepper::FixedUpdate(float deltaTime)
{
}
void dae::PeterPepper::Render() const
{
}

dae::Health* dae::PeterPepper::GetHealth() const
{
	return m_pHealth;
}

void dae::PeterPepper::MoveLeft()
{
	dae::CollisionBox* pCollider = m_pGameObject->GetComponent<dae::CollisionBox>();

	auto collidingWith = pCollider->GetCollidingWith();

	for (dae::CollisionBox* pColliding : collidingWith)
	{
		if (pColliding->GetTag() == "floor")
		{

			if (pColliding->IsPointInCollider(glm::vec2(pCollider->GetPosition().x, pCollider->GetPosition().y + pCollider->GetSize().y)))
			{
				glm::vec3 currentPos = m_pGameObject->GetWorldPosition();
				currentPos.x -= 1;
				currentPos.y = pColliding->GetPosition().y - pCollider->GetSize().y + 5;
				m_pGameObject->SetPosition(currentPos.x, currentPos.y);
				m_pGameObject->GetComponent<dae::AnimationManager>()->SetActiveAnimation("left");
				break;
			}
		}
	}
}

void dae::PeterPepper::MoveRight()
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
				m_pGameObject->GetComponent<dae::AnimationManager>()->SetActiveAnimation("right");
				break;
			}
		}
	}
}

void dae::PeterPepper::IdleForward()
{
	m_pGameObject->GetComponent<dae::AnimationManager>()->SetActiveAnimation("idleForward");
}
void dae::PeterPepper::IdleUp()
{
	m_pGameObject->GetComponent<dae::AnimationManager>()->SetActiveAnimation("idleUp");
}