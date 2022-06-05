#include "BurgerTimePCH.h"
#include "PeterPepper.h"
#include "GameObject.h"
#include "CollisionBox.h"
#include "AnimationManager.h"
#include "MovementComponent.h"
#include "Pepper.h"
#include "Events.h"
#include "PlayerUiComponent.h"
#include "Texture2DComponent.h"
#include "SceneManager.h"

PeterPepper::PeterPepper()
	:m_MoveSpeed(100)
	, m_WidthPlayer(32)
	, m_HeightPlayer(32)
	, m_pCollisionBox(nullptr)
	, m_pMovementComp(nullptr)
	, m_pAnimationComp(nullptr)
	, m_LastLookingDirection(LastLookDir::Right)
	, m_Peppers(5)
	, m_IsActive(false)
	, m_GotHit(false)
	, m_pHealth(nullptr)
	, m_Health(0)
	, m_IsDead(false)
{
}
PeterPepper::~PeterPepper()
{
	if(m_pHealth)
		delete m_pHealth;
}

void PeterPepper::Init(const glm::vec2& spawnPos, int health, int peppers)
{
	m_pCollisionBox = m_pGameObject->AddComponent<dae::CollisionBox>();
	m_pCollisionBox->SetBox(m_WidthPlayer, m_HeightPlayer);
	m_pCollisionBox->SetTag("player");

	m_pMovementComp = m_pGameObject->AddComponent<dae::MovementComponent>();
	m_pMovementComp->SetMovementBox(m_pCollisionBox);
	m_pMovementComp->SetSpeed(m_MoveSpeed);


	m_pAnimationComp = m_pGameObject->AddComponent<dae::AnimationManager>();
	m_pAnimationComp->AddAnimation("PeterPepper/Peter_Up.png", "up", 96, 32, 3, 1, 0.5f);
	m_pAnimationComp->AddAnimation("PeterPepper/Peter_Forward.png", "forward", 96, 32, 3, 1, 0.5f);
	m_pAnimationComp->AddAnimation("PeterPepper/Peter_Left.png", "left", 96, 32, 3, 1, 0.5f);
	m_pAnimationComp->AddAnimation("PeterPepper/Peter_Right.png", "right", 96, 32, 3, 1, 0.5f);
	m_pAnimationComp->AddAnimation("PeterPepper/forward_Idle.png", "idleForward", 32, 32, 1, 1, -1);
	m_pAnimationComp->AddAnimation("PeterPepper/up_Idle.png", "idleUp", 32, 32, 1, 1, -1);
	m_pAnimationComp->AddAnimation("PeterPepper/Peter_Death.png", "death", 192, 32, 6, 1, 0.25);
	m_pAnimationComp->SetActiveAnimation("idleForward");

	m_SpawnPos = spawnPos;
	m_pGameObject->SetPosition(-1000, -1000);

	m_Peppers = peppers;

	m_Health = health;
	m_pHealth = new dae::Health(health);
}

void PeterPepper::Update(float deltaTime)
{
	if (!m_IsActive)
		return;

	if (!m_GotHit || m_IsDead)
		return;

	m_PauseTimer += deltaTime;
	if (m_PauseTimer >= m_PauseTime)
	{
		m_PauseTimer = 0;
		//Notify(*m_pGameObject, Event::PlayerReset);
		m_GotHit = false;
		m_pGameObject->SetPosition(m_SpawnPos.x, m_SpawnPos.y);
		m_pAnimationComp->SetActiveAnimation("idleForward");
	}

}
void PeterPepper::FixedUpdate(float deltaTime)
{
	if (!m_IsActive)
		return;
}
void PeterPepper::Render() const
{
	if (!m_IsActive)
		return;
}

dae::Health* PeterPepper::GetHealth() const
{
	return m_pHealth;
}
int PeterPepper::GetPeppers() const
{
	return m_Peppers;
}

void PeterPepper::MoveLeft()
{
	if (!m_IsActive)
		return;
	if (m_GotHit)
		return;

	if (m_pMovementComp->MoveLeft())
	{
		m_pAnimationComp->SetActiveAnimation("left");
	}
	m_LastLookingDirection = LastLookDir::Left;
}
void PeterPepper::MoveRight()
{
	if (!m_IsActive)
		return;
	if (m_GotHit)
		return;

	if (m_pMovementComp->MoveRight())
	{
		m_pAnimationComp->SetActiveAnimation("right");
	}
	m_LastLookingDirection = LastLookDir::Right;
}
void PeterPepper::MoveUp()
{
	if (!m_IsActive)
		return;
	if (m_GotHit)
		return;

	if (m_pMovementComp->MoveUp())
	{
		m_pAnimationComp->SetActiveAnimation("up");
	}
	m_LastLookingDirection = LastLookDir::Up;
}
void PeterPepper::MoveDown()
{
	if (!m_IsActive)
		return;
	if (m_GotHit)
		return;

	if (m_pMovementComp->MoveDown())
	{
		m_pAnimationComp->SetActiveAnimation("forward");
	}
	m_LastLookingDirection = LastLookDir::Dowm;
}
void PeterPepper::IdleForward()
{
	if (!m_IsActive)
		return;
	if (m_GotHit)
		return;

	m_pAnimationComp->SetActiveAnimation("idleForward");
	m_pMovementComp->Idle();
}
void PeterPepper::IdleUp()
{
	if (!m_IsActive)
		return;

	if (m_GotHit)
		return;

	m_pAnimationComp->SetActiveAnimation("idleUp");
	m_pMovementComp->Idle();
}

void PeterPepper::Pepper()
{
	if (!m_IsActive)
		return;

	if (m_GotHit)
		return;

	if (m_pGameObject->GetChildAt(0)->GetComponent<dae::Pepper>()->OnCooldown())
		return;

	if (m_Peppers == 0)
		return;

	m_Peppers--;
	m_pGameObject->GetChildAt(1)->GetComponent<dae::PlayerUiComponent>()->SetPeppers(m_Peppers);
	switch (m_LastLookingDirection)
	{
	case PeterPepper::LastLookDir::Up:
		m_pGameObject->GetChildAt(0)->GetComponent<dae::Pepper>()->Activate(glm::vec2(m_Transform.GetPosition().x, m_Transform.GetPosition().y - 32));
		break;
	case PeterPepper::LastLookDir::Dowm:
		m_pGameObject->GetChildAt(0)->GetComponent<dae::Pepper>()->Activate(glm::vec2(m_Transform.GetPosition().x, m_Transform.GetPosition().y + 32));
		break;
	case PeterPepper::LastLookDir::Left:
		m_pGameObject->GetChildAt(0)->GetComponent<dae::Pepper>()->Activate(glm::vec2(m_Transform.GetPosition().x - 32, m_Transform.GetPosition().y));
		break;
	case PeterPepper::LastLookDir::Right:
		m_pGameObject->GetChildAt(0)->GetComponent<dae::Pepper>()->Activate(glm::vec2(m_Transform.GetPosition().x + 32, m_Transform.GetPosition().y));
		break;
	}

	Notify(*m_pGameObject, Event::PepperUse);
}

void PeterPepper::Kill()
{
	if (m_GotHit)
		return;

	m_pAnimationComp->SetActiveAnimation("death");
	m_pMovementComp->Idle();
	if (m_pHealth->DealDamage(1) >= 0)
	{
		m_GotHit = true;
		Notify(*m_pGameObject, Event::PlayerHit);
		m_pGameObject->GetChildAt(1)->GetComponent<dae::PlayerUiComponent>()->SetLives(m_pHealth->GetHealth());
	}
	else
	{
		m_GotHit = true;
		m_IsDead = true;
		Notify(*m_pGameObject, Event::playerDead);
	}
}

void PeterPepper::SetActive(bool activity)
{
	m_IsActive = activity;

	if (activity == false)
	{
		m_pGameObject->GetChildAt(1)->GetComponent<dae::PlayerUiComponent>()->SetVisible(false);
		m_pGameObject->GetChildAt(1)->GetComponentAt<dae::Texture2DComponent>(1)->SetVisibility(false);
		m_pGameObject->GetChildAt(1)->GetComponentAt<dae::Texture2DComponent>(2)->SetVisibility(false);
		m_pGameObject->SetPosition(-1000, -1000);
	}
	else
	{
		m_pGameObject->SetPosition(m_SpawnPos.x, m_SpawnPos.y);
		m_pGameObject->GetChildAt(1)->GetComponentAt<dae::Texture2DComponent>(1)->SetVisibility(true);
		m_pGameObject->GetChildAt(1)->GetComponentAt<dae::Texture2DComponent>(2)->SetVisibility(true);
		Notify(*m_pGameObject, Event::PlayerActivated);
	}
}
bool PeterPepper::GetActive() const
{
	return m_IsActive;
}
bool PeterPepper::IsDead() const
{
	return (m_GotHit || m_IsDead);
}
void PeterPepper::SetSpawn(glm::vec2 spawnPoint)
{
	m_SpawnPos = spawnPoint;
}
void PeterPepper::MoveToSpawn()
{
	m_pGameObject->SetPosition(m_SpawnPos.x, m_SpawnPos.y);
}

void PeterPepper::Reset()
{
	m_GotHit = false;
	m_IsDead = false;
	m_Peppers = 5;
	m_pHealth->SetHealth(m_Health);

	dae::PlayerUiComponent* ui = m_pGameObject->GetChildAt(1)->GetComponent<dae::PlayerUiComponent>();
	ui->SetLives(m_Health);
	ui->SetPeppers(m_Peppers);
	//ui->SetScore(0);

	m_pAnimationComp->SetActiveAnimation("idleForward");
}