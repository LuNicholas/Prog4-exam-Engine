#include "MiniginPCH.h"
#include "Command.h"
#include "GameObject.h"
#include "PeterPepper.h"
#include "PlayerUiComponent.h"
#include "CollisionBox.h"
#include "Sound.h"
#include "AnimationManager.h"
#include "Events.h"


//HitpepperCOmmand
HitCommand::HitCommand(dae::GameObject* actor)
	:m_actor(actor)
{
}
void HitCommand::Execute()
{
	dae::PeterPepper* peterPepper = m_actor->GetComponent<dae::PeterPepper>();
	if (peterPepper != nullptr)
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
	m_actor->GetComponent<dae::PeterPepper>()->MoveLeft();
}

//MoveRight Command
MoveRight::MoveRight(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void MoveRight::Execute()
{
	m_actor->GetComponent<dae::PeterPepper>()->MoveRight();
}

MoveUp::MoveUp(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void MoveUp::Execute()
{
	m_actor->GetComponent<dae::PeterPepper>()->MoveUp();
}
MoveDown::MoveDown(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void MoveDown::Execute()
{
	m_actor->GetComponent<dae::PeterPepper>()->MoveDown();
}

IdleForward::IdleForward(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void IdleForward::Execute()
{
	m_actor->GetComponent<dae::PeterPepper>()->IdleForward();
}
IdleUp::IdleUp(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void IdleUp::Execute()
{
	m_actor->GetComponent<dae::PeterPepper>()->IdleUp();
}


//play sound

PlaySound::PlaySound(int id)
	:m_SoundId(id)
{

}
void PlaySound::Execute()
{
	SoundServiceLocator::GetSoundSystem().Play(m_SoundId, 10);
}