#include "MiniginPCH.h"
#include "Command.h"
#include "GameObject.h"
#include "PeterPepper.h"
#include "PlayerUiComponent.h"


//HitpepperCOmmand
HitCommand::HitCommand(dae::GameObject* actor)
	:m_actor(actor)
{
}
void HitCommand::Execute()
{
	dae::PeterPepper* peterPepper = m_actor->GetComponent<dae::PeterPepper>();
	if(peterPepper != nullptr)
		peterPepper->GetHealth()->DealDamage(1, *m_actor);
}

//BunDropped
BunDropped::BunDropped(dae::GameObject* actor)
	:m_actor(actor)
{
}
void BunDropped::Execute()
{
	auto ui = m_actor->GetComponent<dae::PlayerUiComponent>();
	Notify(*m_actor, Event::BunDropped);
}

//MoveLeft Command
MoveLeft::MoveLeft(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void MoveLeft::Execute()
{
	glm::vec3 currentPos = m_actor->GetWorldPosition();

	currentPos.x += 1;

	m_actor->SetPosition(currentPos.x, currentPos.y);
}

//MoveRight Command
MoveRight::MoveRight(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void MoveRight::Execute()
{
	glm::vec3 currentPos = m_actor->GetWorldPosition();

	currentPos.x -= 1;

	m_actor->SetPosition(currentPos.x, currentPos.y);
}