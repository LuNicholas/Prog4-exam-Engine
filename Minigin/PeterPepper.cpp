#include "MiniginPCH.h"
#include "PeterPepper.h"

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