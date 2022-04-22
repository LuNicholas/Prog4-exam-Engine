#include "MiniginPCH.h"
#include "Health.h"
#include "GameObject.h"
#include "Observer.h"

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
void dae::Health::DealDamage(int damage, const GameObject& hitGameObject)
{
	m_currentHealth -= damage;
	if (m_currentHealth < 0)
	{
		m_currentHealth = 0;
	}

	Notify(hitGameObject, Event::PlayerHit);
}