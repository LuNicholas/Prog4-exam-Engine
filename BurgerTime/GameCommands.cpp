#include "BurgerTimePCH.h"
#include "GameCommands.h"
#include "Command.h"
#include "GameObject.h"
#include "PeterPepper.h"
#include "PlayerUiComponent.h"
#include "CollisionBox.h"
#include "Sound.h"
#include "AnimationManager.h"
#include "Events.h"
#include "SceneManager.h"//todo remove this probs after tests
#include "ButtonManager.h"


//pepperCOmmand
PepperCommand::PepperCommand(dae::GameObject* actor)
	:m_actor(actor)
{
}
void PepperCommand::Execute()
{
	m_actor->GetComponent<PeterPepper>()->Pepper();
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
	m_actor->GetComponent<PeterPepper>()->MoveLeft();
}

//MoveRight Command
MoveRight::MoveRight(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void MoveRight::Execute()
{
	m_actor->GetComponent<PeterPepper>()->MoveRight();
}

MoveUp::MoveUp(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void MoveUp::Execute()
{
	m_actor->GetComponent<PeterPepper>()->MoveUp();
}
MoveDown::MoveDown(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void MoveDown::Execute()
{
	m_actor->GetComponent<PeterPepper>()->MoveDown();
}

IdleForward::IdleForward(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void IdleForward::Execute()
{
	m_actor->GetComponent<PeterPepper>()->IdleForward();
}
IdleUp::IdleUp(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void IdleUp::Execute()
{
	m_actor->GetComponent<PeterPepper>()->IdleUp();
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



NextScene::NextScene()
{

}
void NextScene::Execute()
{
	dae::SceneManager::GetInstance().NextScene();
}


NextButton::NextButton(ButtonManager* buttonManager)
	:m_pButtonManager(buttonManager)
{

}
void NextButton::Execute()
{
	m_pButtonManager->NextButton();
}

PreviousButton::PreviousButton(ButtonManager* buttonManager)
	:m_pButtonManager(buttonManager)
{

}
void PreviousButton::Execute()
{
	m_pButtonManager->PreviousButton();
}
