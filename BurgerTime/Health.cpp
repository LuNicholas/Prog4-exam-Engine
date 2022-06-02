#include "BurgerTimePCH.h"
#include "Health.h"
#include "GameObject.h"
#include "Observer.h"
#include "Events.h"

dae::Health::Health(int startHealth)
	:m_currentHealth{ startHealth }
{

}
dae::Health::~Health()
{

}


int dae::Health::GetHealth() const
{
	return m_currentHealth;
}
void dae::Health::SetHealth(int health)
{
	m_currentHealth = health;
}


int dae::Health::DealDamage(int damage)
{
	m_currentHealth -= damage;
	return m_currentHealth;
}