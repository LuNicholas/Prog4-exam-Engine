#include "MiniginPCH.h"
#include "Pepper.h"
#include "GameObject.h"
#include "CollisionBox.h"
#include "AnimationManager.h"


dae::Pepper::Pepper()
	:m_OnCooldown(false)
{
}
dae::Pepper::~Pepper()
{
}

void dae::Pepper::Init()
{
	CollisionBox* pepperCol = m_pGameObject->AddComponent<CollisionBox>();
	pepperCol->SetBox(32, 32);

	m_pAnimationComp = m_pGameObject->AddComponent<AnimationManager>();
	m_pAnimationComp->AddAnimation("Pepper_Right.png", "right", 128, 32, 4, 1, 0.5f);
	m_pAnimationComp->SetActiveAnimation("right");
}


void dae::Pepper::Update(float deltaTime)
{
}
void dae::Pepper::FixedUpdate(float deltaTime)
{
}
void dae::Pepper::Render() const
{
}


