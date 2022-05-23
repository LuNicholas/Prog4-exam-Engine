#include "MiniginPCH.h"
#include "PeterPepper.h"
#include "GameObject.h"
#include "CollisionBox.h"

dae::PeterPepper::PeterPepper()
{
	m_pHealth = new dae::Health(3);
}
dae::PeterPepper::~PeterPepper()
{
	delete m_pHealth;
}

void dae::PeterPepper::Update(float deltaTime)
{
	CollisionBox* collision = m_pGameObject->GetComponent<CollisionBox>();
	if (collision != nullptr)
	{
		auto test = collision->GetCollidingWith();
		if (test.size() > 0)
		{
			std::cout << "im collidng \n";
		}
	}
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