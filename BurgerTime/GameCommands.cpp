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
#include "Scene.h"


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



NextScene::NextScene(ButtonManager* buttonManager, PeterPepper* player1, PeterPepper* player2)
	:m_pButtonManager(buttonManager)
	, m_pPlayer1(player1)
	, m_pPlayer2(player2)
{

}
void NextScene::Execute()
{
	if (dae::SceneManager::GetInstance().GetCurrentScene().GetSceneName() == dae::SceneManager::GetInstance().GetScene("mainMenu").GetSceneName())
	{
		dae::SceneManager::GetInstance().NextScene();

		switch (m_pButtonManager->GetCurrentButton())
		{
		case 0:
		{
			m_pPlayer1->SetActive(true);
			m_pPlayer2->SetActive(false);
			break;
		}
		case 1:
		{
			m_pPlayer1->SetActive(true);
			m_pPlayer2->SetActive(true);
			break;
		}
		case 2:
		{
			//m_pPlayer2->GetGameObject()->GetComponent<dae::CollisionBox>()->SetTag()
			break;
		}
		}
	}
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
