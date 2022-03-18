#include "MiniginPCH.h"
#include "Command.h"
#include "GameObject.h"
#include "HealthComponent.h"


//HitpepperCOmmand
HitPepperCommand::HitPepperCommand(dae::GameObject* pepper)
	:m_pepper(pepper)
{
}
void HitPepperCommand::Execute()
{
	dae::HealthComponent* health = m_pepper->GetComponent<dae::HealthComponent>();
	health->DealDamage(1, *m_pepper);
}