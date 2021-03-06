#include "BurgerTimePCH.h"
#include "MovementComponent.h"
#include "CollisionBox.h"
#include "GameObject.h"

dae::MovementComponent::MovementComponent()
	:m_FloorOffset(5)
	, m_pCollisionBox(nullptr)
	, m_Speed(1)
	, m_CurrentMoveState(MovementState::idle)
	, m_pLastLadder(nullptr)
{
}
dae::MovementComponent::~MovementComponent()
{
}

void dae::MovementComponent::SetMovementBox(CollisionBox* pCollisionBox)
{
	m_pCollisionBox = pCollisionBox;
}
void dae::MovementComponent::SetSpeed(float speed)
{
	m_Speed = speed;
}

void dae::MovementComponent::Update(float deltaTime)
{
	glm::vec3 currentPos;

	switch (m_CurrentMoveState)
	{
	case dae::MovementComponent::MovementState::up:
		if (!MoveUp())
			break;
		currentPos = m_pGameObject->GetWorldPosition();
		currentPos.y -= (m_Speed * deltaTime);
		m_pGameObject->SetPosition(currentPos.x, currentPos.y);
		break;
	case dae::MovementComponent::MovementState::down:
		if (!MoveDown())
			break;
		currentPos = m_pGameObject->GetWorldPosition();
		currentPos.y += (m_Speed * deltaTime);
		m_pGameObject->SetPosition(currentPos.x, currentPos.y);
		break;
	case dae::MovementComponent::MovementState::left:
		if (!MoveLeft())
			break;
		currentPos = m_pGameObject->GetWorldPosition();
		currentPos.x -= (m_Speed * deltaTime);
		currentPos.y = currentPos.y;
		m_pGameObject->SetPosition(currentPos.x, currentPos.y);
		break;
	case dae::MovementComponent::MovementState::right:
		if (!MoveRight())
			break;
		currentPos = m_pGameObject->GetWorldPosition();
		currentPos.x += (m_Speed * deltaTime);
		currentPos.y = currentPos.y;
		m_pGameObject->SetPosition(currentPos.x, currentPos.y);
		break;
	case dae::MovementComponent::MovementState::idle:
		break;
	default:
		break;
	}
}
void dae::MovementComponent::FixedUpdate(float deltaTime)
{
}
void dae::MovementComponent::Render() const
{
}


bool dae::MovementComponent::MoveUp()
{
	auto collidingWith = m_pCollisionBox->GetCollidingWith();

	for (dae::CollisionBox* pColliding : collidingWith)
	{
		if (pColliding->GetTag() == "Ladder")
		{
			if (pColliding->IsPointInCollider(glm::vec2(m_pCollisionBox->GetPosition().x + m_pCollisionBox->GetSize().x / 2,
				m_pCollisionBox->GetPosition().y)))
			{
				m_CurrentMoveState = MovementState::up;
				m_pLastLadder = pColliding;
				return true;
			}
		}
	}
	m_CurrentMoveState = MovementState::idle;
	return false;
}
bool dae::MovementComponent::MoveDown()
{
	auto collidingWith = m_pCollisionBox->GetCollidingWith();

	for (dae::CollisionBox* pColliding : collidingWith)
	{
		if (pColliding->GetTag() == "Ladder")
		{
			if (pColliding->IsPointInCollider(glm::vec2(m_pCollisionBox->GetPosition().x + m_pCollisionBox->GetSize().x / 2,
				m_pCollisionBox->GetPosition().y + m_pCollisionBox->GetSize().y)))
			{
				m_CurrentMoveState = MovementState::down;
				m_pLastLadder = pColliding;
				return true;
			}
		}
	}
	m_CurrentMoveState = MovementState::idle;
	return false;
}
bool dae::MovementComponent::MoveLeft()
{
	auto collidingWith = m_pCollisionBox->GetCollidingWith();

	for (dae::CollisionBox* pColliding : collidingWith)
	{
		if (pColliding->GetTag() == "floor")
		{

			if (pColliding->IsPointInCollider(glm::vec2(m_pCollisionBox->GetPosition().x,
				m_pCollisionBox->GetPosition().y + m_pCollisionBox->GetSize().y)))
			{
				glm::vec3 currentPos = m_pGameObject->GetWorldPosition();
				//currentPos.x -= m_Speed;
				currentPos.y = pColliding->GetPosition().y - m_pCollisionBox->GetSize().y + m_FloorOffset;
				m_pGameObject->SetPosition(currentPos.x, currentPos.y);
				m_CurrentMoveState = MovementState::left;
				return true;
			}
		}
	}
	m_CurrentMoveState = MovementState::idle;
	return false;
}
bool dae::MovementComponent::MoveRight()
{
	auto collidingWith = m_pCollisionBox->GetCollidingWith();

	for (dae::CollisionBox* pColliding : collidingWith)
	{
		if (pColliding->GetTag() == "floor")
		{

			if (pColliding->IsPointInCollider(glm::vec2(m_pCollisionBox->GetPosition().x + m_pCollisionBox->GetSize().x,
				m_pCollisionBox->GetPosition().y + m_pCollisionBox->GetSize().y)))
			{
				glm::vec3 currentPos = m_pGameObject->GetWorldPosition();
				//currentPos.x += m_Speed;
				currentPos.y = pColliding->GetPosition().y - m_pCollisionBox->GetSize().y + m_FloorOffset;
				m_pGameObject->SetPosition(currentPos.x, currentPos.y);
				m_CurrentMoveState = MovementState::right;
				return true;
			}
		}
	}
	m_CurrentMoveState = MovementState::idle;
	return false;
}

bool dae::MovementComponent::OnPlatform()
{
	auto collidingWith = m_pCollisionBox->GetCollidingWith();

	for (dae::CollisionBox* pColliding : collidingWith)
	{
		if (pColliding->GetTag() == "floor")
		{
			if (pColliding->IsPointInCollider(glm::vec2(m_pCollisionBox->GetPosition().x + m_pCollisionBox->GetSize().x,
				m_pCollisionBox->GetPosition().y + m_pCollisionBox->GetSize().y)))
			{
				return true;
			}
		}
	}
	return false;
}
bool dae::MovementComponent::TouchingLadder()
{
	auto collidingWith = m_pCollisionBox->GetCollidingWith();

	for (dae::CollisionBox* pColliding : collidingWith)
	{
		if (pColliding->GetTag() == "Ladder")
		{
			if (pColliding->IsPointInCollider(glm::vec2(m_pCollisionBox->GetPosition().x + m_pCollisionBox->GetSize().x / 2,
				m_pCollisionBox->GetPosition().y + m_pCollisionBox->GetSize().y)))
			{
				m_pLastLadder = pColliding;
				return true;
			}
		}
	}
	return false;
}

dae::CollisionBox* dae::MovementComponent::GetLastLadder()
{
	return m_pLastLadder;
}
void dae::MovementComponent::Idle()
{
	m_CurrentMoveState = MovementState::idle;
}