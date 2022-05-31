#include "MiniginPCH.h"
#include "PeterPepper.h"
#include "GameObject.h"
#include "CollisionBox.h"
#include "AnimationManager.h"
#include "MovementComponent.h"

dae::PeterPepper::PeterPepper()
	:m_MoveSpeed(10)
	, m_WidthPlayer(32)
	, m_HeightPlayer(32)
	, m_pCollisionBox(nullptr)
	, m_pMovementComp(nullptr)
	, m_pAnimationComp(nullptr)
{
	m_pHealth = new dae::Health(3);
}
dae::PeterPepper::~PeterPepper()
{
	delete m_pHealth;
}

void dae::PeterPepper::Init()
{
	m_pCollisionBox = m_pGameObject->AddComponent<CollisionBox>();
	m_pCollisionBox->SetBox(m_WidthPlayer, m_HeightPlayer);
	m_pCollisionBox->SetTag("player");

	m_pMovementComp = m_pGameObject->AddComponent<MovementComponent>();
	m_pMovementComp->SetMovementBox(m_pCollisionBox);



	m_pAnimationComp = m_pGameObject->AddComponent<AnimationManager>();
	m_pAnimationComp->AddAnimation("Peter_Up.png", "up", 96, 32, 3, 1, 0.5f);
	m_pAnimationComp->AddAnimation("Peter_Forward.png", "forward", 96, 32, 3, 1, 0.5f);
	m_pAnimationComp->AddAnimation("Peter_Left.png", "left", 96, 32, 3, 1, 0.5f);
	m_pAnimationComp->AddAnimation("Peter_Right.png", "right", 96, 32, 3, 1, 0.5f);
	m_pAnimationComp->AddAnimation("forward_Idle.png", "idleForward", 32, 32, 1, 1, -1);
	m_pAnimationComp->AddAnimation("up_Idle.png", "idleUp", 32, 32, 1, 1, -1);
	m_pAnimationComp->SetActiveAnimation("idleForward");

}

void dae::PeterPepper::Update(float deltaTime)
{
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
	if (m_pMovementComp->MoveLeft())
	{
		m_pAnimationComp->SetActiveAnimation("left");
	}
}

void dae::PeterPepper::MoveRight()
{
	if (m_pMovementComp->MoveRight())
	{
		m_pAnimationComp->SetActiveAnimation("right");
	}
}
void dae::PeterPepper::MoveUp()
{
	if (m_pMovementComp->MoveUp())
	{
		m_pAnimationComp->SetActiveAnimation("up");
	}
}
void dae::PeterPepper::MoveDown()
{
	if (m_pMovementComp->MoveDown())
	{
		m_pAnimationComp->SetActiveAnimation("forward");
	}
}

void dae::PeterPepper::IdleForward()
{
	m_pAnimationComp->SetActiveAnimation("idleForward");
}
void dae::PeterPepper::IdleUp()
{
	m_pAnimationComp->SetActiveAnimation("idleUp");
}