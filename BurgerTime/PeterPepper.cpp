#include "BurgerTimePCH.h"
#include "PeterPepper.h"
#include "GameObject.h"
#include "CollisionBox.h"
#include "AnimationManager.h"
#include "MovementComponent.h"
#include "Pepper.h"

PeterPepper::PeterPepper()
	:m_MoveSpeed(10)
	, m_WidthPlayer(32)
	, m_HeightPlayer(32)
	, m_pCollisionBox(nullptr)
	, m_pMovementComp(nullptr)
	, m_pAnimationComp(nullptr)
	, m_LastLookingDirection(LastLookDir::Right)
{
	m_pHealth = new dae::Health(3);

	
}
PeterPepper::~PeterPepper()
{
	delete m_pHealth;
}

void PeterPepper::Init()
{
	m_pCollisionBox = m_pGameObject->AddComponent<dae::CollisionBox>();
	m_pCollisionBox->SetBox(m_WidthPlayer, m_HeightPlayer);
	m_pCollisionBox->SetTag("player");

	m_pMovementComp = m_pGameObject->AddComponent<dae::MovementComponent>();
	m_pMovementComp->SetMovementBox(m_pCollisionBox);


	m_pAnimationComp = m_pGameObject->AddComponent<dae::AnimationManager>();
	m_pAnimationComp->AddAnimation("Peter_Up.png", "up", 96, 32, 3, 1, 0.5f);
	m_pAnimationComp->AddAnimation("Peter_Forward.png", "forward", 96, 32, 3, 1, 0.5f);
	m_pAnimationComp->AddAnimation("Peter_Left.png", "left", 96, 32, 3, 1, 0.5f);
	m_pAnimationComp->AddAnimation("Peter_Right.png", "right", 96, 32, 3, 1, 0.5f);
	m_pAnimationComp->AddAnimation("forward_Idle.png", "idleForward", 32, 32, 1, 1, -1);
	m_pAnimationComp->AddAnimation("up_Idle.png", "idleUp", 32, 32, 1, 1, -1);
	m_pAnimationComp->SetActiveAnimation("idleForward");
}

void PeterPepper::Update(float deltaTime)
{
}
void PeterPepper::FixedUpdate(float deltaTime)
{
}
void PeterPepper::Render() const
{
}

dae::Health* PeterPepper::GetHealth() const
{
	return m_pHealth;
}

void PeterPepper::MoveLeft()
{
	if (m_pMovementComp->MoveLeft())
	{
		m_pAnimationComp->SetActiveAnimation("left");
	}
	m_LastLookingDirection = LastLookDir::Left;
}

void PeterPepper::MoveRight()
{
	if (m_pMovementComp->MoveRight())
	{
		m_pAnimationComp->SetActiveAnimation("right");
	}
	m_LastLookingDirection = LastLookDir::Right;
}
void PeterPepper::MoveUp()
{
	if (m_pMovementComp->MoveUp())
	{
		m_pAnimationComp->SetActiveAnimation("up");
	}
	m_LastLookingDirection = LastLookDir::Up;
}
void PeterPepper::MoveDown()
{
	if (m_pMovementComp->MoveDown())
	{
		m_pAnimationComp->SetActiveAnimation("forward");
	}
	m_LastLookingDirection = LastLookDir::Dowm;
}

void PeterPepper::IdleForward()
{
	m_pAnimationComp->SetActiveAnimation("idleForward");
}
void PeterPepper::IdleUp()
{
	m_pAnimationComp->SetActiveAnimation("idleUp");
}

void PeterPepper::Pepper()
{
	switch (m_LastLookingDirection)
	{
	case PeterPepper::LastLookDir::Up:
		m_pGameObject->GetChildAt(0)->GetComponent<dae::Pepper>()->Activate(glm::vec2(m_Transform.GetPosition().x, m_Transform.GetPosition().y - 32));
		//m_pGameObject->GetChildAt(0)->SetPosition(m_Transform.GetPosition().x, m_Transform.GetPosition().y - 32);
		break;
	case PeterPepper::LastLookDir::Dowm:
		m_pGameObject->GetChildAt(0)->GetComponent<dae::Pepper>()->Activate(glm::vec2(m_Transform.GetPosition().x, m_Transform.GetPosition().y + 32));
		//m_pGameObject->GetChildAt(0)->SetPosition(m_Transform.GetPosition().x, m_Transform.GetPosition().y + 32);
		break;
	case PeterPepper::LastLookDir::Left:
		m_pGameObject->GetChildAt(0)->GetComponent<dae::Pepper>()->Activate(glm::vec2(m_Transform.GetPosition().x - 32, m_Transform.GetPosition().y));
		//m_pGameObject->GetChildAt(0)->SetPosition(m_Transform.GetPosition().x - 32, m_Transform.GetPosition().y);
		break;
	case PeterPepper::LastLookDir::Right:
		m_pGameObject->GetChildAt(0)->GetComponent<dae::Pepper>()->Activate(glm::vec2(m_Transform.GetPosition().x + 32, m_Transform.GetPosition().y));
		//m_pGameObject->GetChildAt(0)->SetPosition(m_Transform.GetPosition().x + 32, m_Transform.GetPosition().y);
		break;
	}
	
}