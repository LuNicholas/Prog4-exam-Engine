#include "MiniginPCH.h"
#include "Command.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "PlayerUiComponent.h"


//HitpepperCOmmand
HitCommand::HitCommand(dae::GameObject* actor)
	:m_actor(actor)
{
}
void HitCommand::Execute()
{
	dae::HealthComponent* health = m_actor->GetComponent<dae::HealthComponent>();
	health->DealDamage(1, *m_actor);
}

//AddSoreCOmmand
AddScoreCommand::AddScoreCommand(dae::GameObject* actor)
	:m_actor(actor)
{
}
void AddScoreCommand::Execute()
{
	//auto ui = m_actor->GetComponent<dae::PlayerUiComponent>();
	Notify(*m_actor, Event::ScoreIncrease);
}