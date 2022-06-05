#include "BurgerTimePCH.h"
#include "EnemyPlayer.h"
#include "GameObject.h"
#include "AnimationManager.h"
#include "CollisionBox.h"
#include "MovementComponent.h"
#include "PeterPepper.h"
#include "Events.h"


EnemyPlayer::EnemyPlayer()
	:m_pAnimationComp(nullptr)
	, m_pCollisionBox(nullptr)
	, m_pMovementComp(nullptr)
	, m_pPlayer(nullptr)
	, m_Width(32)
	, m_Height(32)
	, m_SpawnPos(-1000, -1000)
	, m_MoveSpeed(85)
	, m_Stunned(false)
	, m_StunTime(2.f)
	, m_StunTimer(0)
	, m_Dead(false)
	, m_IsActive(false)
	, m_Paused(false)
	, m_DeathTime(4.f)
	, m_DeathTimer(0.f)
{
}
EnemyPlayer::~EnemyPlayer()
{
}

void EnemyPlayer::Init(PeterPepper* player)
{
	m_pCollisionBox = m_pGameObject->AddComponent<dae::CollisionBox>();
	m_pCollisionBox->SetBox(m_Width, m_Height);
	m_pCollisionBox->SetTag("enemyPlayer");

	m_pMovementComp = m_pGameObject->AddComponent<dae::MovementComponent>();
	m_pMovementComp->SetMovementBox(m_pCollisionBox);
	m_pMovementComp->SetSpeed(m_MoveSpeed);


	m_pAnimationComp = m_pGameObject->AddComponent<dae::AnimationManager>();
	m_pAnimationComp->AddAnimation("Enemies/Bean/Bean_Up.png", "up", 64, 32, 2, 1, 0.5f);
	m_pAnimationComp->AddAnimation("Enemies/Bean/Bean_Down.png", "down", 64, 32, 2, 1, 0.5f);
	m_pAnimationComp->AddAnimation("Enemies/Bean/Bean_Left.png", "left", 64, 32, 2, 1, 0.5f);
	m_pAnimationComp->AddAnimation("Enemies/Bean/Bean_Right.png", "right", 64, 32, 2, 1, 0.5f);
	m_pAnimationComp->AddAnimation("Enemies/Bean/Bean_Death.png", "death", 128, 32, 4, 1, 0.5f);
	m_pAnimationComp->AddAnimation("Enemies/Bean/Bean_Stunned.png", "stunned", 64, 32, 2, 1, 0.25f);
	m_pAnimationComp->SetActiveAnimation("down");

	m_pGameObject->SetPosition(-1000, -1000);

	m_pPlayer = player;
	m_pPlayerCollisionBox = player->GetGameObject()->GetComponent<dae::CollisionBox>();
}

void EnemyPlayer::Update(float deltaTime)
{
	if (!m_IsActive || m_Paused)
		return;

	if (m_Dead)
	{
		m_DeathTimer += deltaTime;
		if (m_DeathTimer > m_DeathTime)
		{
			m_DeathTimer = 0;
			m_Dead = false;
			m_pGameObject->SetPosition(m_SpawnPos.x, m_SpawnPos.y);
		}
	}

	if (m_Stunned)
	{
		m_StunTimer += deltaTime;
		if (m_StunTimer > m_StunTime)
		{
			m_StunTimer = 0;
			m_Stunned = false;
		}
		return;
	}

	if (m_pCollisionBox->IsOverlappingWith(m_pPlayerCollisionBox))
	{
		m_pPlayer->Kill();
		m_Paused = true;
		m_pMovementComp->Idle();
	}
}
void EnemyPlayer::FixedUpdate(float deltaTime)
{
	if (!m_IsActive)
		return;
}
void EnemyPlayer::Render() const
{
	if (!m_IsActive)
		return;
}


void EnemyPlayer::Kill()
{
	m_pAnimationComp->SetActiveAnimation("death");
	m_Dead = true;
}

void EnemyPlayer::MoveLeft()
{
	if (!m_IsActive)
		return;
	if (m_Stunned || m_Dead || m_Paused)
		return;

	if (m_pMovementComp->MoveLeft())
	{
		m_pAnimationComp->SetActiveAnimation("left");
	}
}
void EnemyPlayer::MoveRight()
{
	if (!m_IsActive)
		return;
	if (m_Stunned || m_Dead || m_Paused)
		return;

	if (m_pMovementComp->MoveRight())
	{
		m_pAnimationComp->SetActiveAnimation("right");
	}
}
void EnemyPlayer::MoveUp()
{
	if (!m_IsActive)
		return;
	if (m_Stunned || m_Dead || m_Paused)
		return;

	if (m_pMovementComp->MoveUp())
	{
		m_pAnimationComp->SetActiveAnimation("up");
	}
}
void EnemyPlayer::MoveDown()
{
	if (!m_IsActive)
		return;
	if (m_Stunned || m_Dead || m_Paused)
		return;

	if (m_pMovementComp->MoveDown())
	{
		m_pAnimationComp->SetActiveAnimation("down");
	}
}
void EnemyPlayer::IdleForward()
{
	if (!m_IsActive)
		return;
	if (m_Stunned || m_Dead || m_Paused)
		return;
	m_pMovementComp->Idle();
}
void EnemyPlayer::IdleUp()
{
	if (!m_IsActive)
		return;

	if (m_Stunned || m_Dead || m_Paused)
		return;
	m_pMovementComp->Idle();
}

void EnemyPlayer::SetActive(bool active)
{
	m_IsActive = active;
	Notify(*m_pGameObject, Event::enemyPlayerActivated);
}
bool EnemyPlayer::GetIsActive() const
{
	return m_IsActive;
}
bool EnemyPlayer::GetIsDead() const
{
	return m_Dead;
}
void EnemyPlayer::SetSpawn(const glm::vec2& spawnPos)
{
	m_SpawnPos = spawnPos;
}
void EnemyPlayer::SetStunned(bool stunned)
{
	m_Stunned = true;
	m_pAnimationComp->SetActiveAnimation("stunned");
}
void EnemyPlayer::SetPaused(bool paused)
{
	m_Paused = paused;
	m_pAnimationComp->SetActiveAnimation("down");
}