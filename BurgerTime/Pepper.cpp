#include "BurgerTimePCH.h"
#include "Pepper.h"
#include "GameObject.h"
#include "CollisionBox.h"
#include "AnimationManager.h"
#include "Enemy.h"
#include "EnemyPlayer.h"


dae::Pepper::Pepper()
	:m_OnCooldown(false)
	, m_CooldownTime(1.f)
	, m_CurrentCdTime(0)
	, m_pCollisionBox(nullptr)
	, m_pAnimationComp(nullptr)
{
}
dae::Pepper::~Pepper()
{
}

void dae::Pepper::Init()
{
	m_pCollisionBox = m_pGameObject->AddComponent<CollisionBox>();
	m_pCollisionBox->SetBox(32, 32);

	m_pAnimationComp = m_pGameObject->AddComponent<AnimationManager>();
	m_pAnimationComp->AddAnimation("PeterPepper/Pepper_Right.png", "right", 128, 32, 4, 1, 0.25f);
	m_pAnimationComp->SetActiveAnimation("right");
}


void dae::Pepper::Update(float deltaTime)
{
	if (m_OnCooldown)
	{
		for (dae::CollisionBox* pColliding : m_pCollisionBox->GetCollidingWith())
		{
			if (pColliding->GetTag() == "enemy")
			{
				pColliding->GetGameObject()->GetComponent<Enemy>()->SetStunned();
			}
			else if (pColliding->GetTag() == "enemyPlayer")
			{
				pColliding->GetGameObject()->GetComponent<EnemyPlayer>()->SetStunned(true);
			}
		}

		m_CurrentCdTime += deltaTime;
		if (m_CurrentCdTime >= m_CooldownTime)
		{
			m_CurrentCdTime = 0;
			m_OnCooldown = false;
			m_pGameObject->SetPosition(-1000, 1000);//put outside of screen
		}
	}
}
void dae::Pepper::FixedUpdate(float deltaTime)
{
}
void dae::Pepper::Render() const
{
}

void dae::Pepper::Activate(glm::vec2 pos)
{
	if (!m_OnCooldown)
	{
		m_pAnimationComp->ResetAnimation();
		m_pGameObject->SetPosition(pos.x, pos.y);
		m_OnCooldown = true;
	}
}

bool dae::Pepper::OnCooldown() const
{
	return m_OnCooldown;
}