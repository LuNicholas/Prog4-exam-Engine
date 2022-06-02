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
//void dae::Health::DealDamage(int damage, const GameObject& hitGameObject)
int dae::Health::DealDamage(int damage)
{
	m_currentHealth -= damage;
	//if (m_currentHealth < 0)
	//{
	//	m_currentHealth = 0;
	//	//otify(hitGameObject, Event::PlayerHit);//GAME OVER
	//}
	//else
	//{
	//	//Notify(hitGameObject, Event::PlayerHit);
	//}
	return m_currentHealth;
}