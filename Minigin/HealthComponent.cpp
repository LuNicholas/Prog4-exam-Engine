#include "MiniginPCH.h"
#include "HealthComponent.h"

dae::HealthComponent::HealthComponent()
{

}
dae::HealthComponent::~HealthComponent()
{

}

void dae::HealthComponent::Update(float)
{
}
void dae::HealthComponent::FixedUpdate(float)
{
}
void dae::HealthComponent::Render() const
{
}

int dae::HealthComponent::GetHealth()
{
	return m_currentHealth;
}
void dae::HealthComponent::SetHealth(int health)
{
	m_currentHealth = health;
}
void dae::HealthComponent::DealDamage(int damage)
{
	m_currentHealth -= damage;
}