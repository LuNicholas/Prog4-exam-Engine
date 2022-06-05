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
#include "EnemyPlayer.h"
#include "MovementComponent.h"


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
	PeterPepper* peter = m_actor->GetComponent<PeterPepper>();
	if (peter != nullptr)
		peter->MoveLeft();
	else
		m_actor->GetComponent<EnemyPlayer>()->MoveLeft();
}

//MoveRight Command
MoveRight::MoveRight(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void MoveRight::Execute()
{
	PeterPepper* peter = m_actor->GetComponent<PeterPepper>();
	if (peter != nullptr)
		peter->MoveRight();
	else
		m_actor->GetComponent<EnemyPlayer>()->MoveRight();
}

MoveUp::MoveUp(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void MoveUp::Execute()
{
	PeterPepper* peter = m_actor->GetComponent<PeterPepper>();
	if (peter != nullptr)
		peter->MoveUp();
	else
		m_actor->GetComponent<EnemyPlayer>()->MoveUp();
}
MoveDown::MoveDown(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void MoveDown::Execute()
{
	PeterPepper* peter = m_actor->GetComponent<PeterPepper>();
	if (peter != nullptr)
		peter->MoveDown();
	else
		m_actor->GetComponent<EnemyPlayer>()->MoveDown();
}

IdleForward::IdleForward(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void IdleForward::Execute()
{
	PeterPepper* peter = m_actor->GetComponent<PeterPepper>();
	if (peter != nullptr)
		peter->IdleForward();
	else
		m_actor->GetComponent<EnemyPlayer>()->IdleForward();

}
IdleUp::IdleUp(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void IdleUp::Execute()
{
	PeterPepper* peter = m_actor->GetComponent<PeterPepper>();
	if (peter != nullptr)
		peter->IdleUp();
	else
		m_actor->GetComponent<EnemyPlayer>()->IdleForward();
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



NextScene::NextScene(ButtonManager* buttonManager, PeterPepper* player1, PeterPepper* player2, EnemyPlayer* enemy)
	:m_pButtonManager(buttonManager)
	, m_pPlayer1(player1)
	, m_pPlayer2(player2)
	, m_pEnemy(enemy)
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
			m_pEnemy->SetActive(false);
			break;
		}
		case 1:
		{
			m_pPlayer1->SetActive(true);
			m_pPlayer2->SetActive(true);
			m_pEnemy->SetActive(false);
			break;
		}
		case 2:
		{
			m_pPlayer1->SetActive(true);
			m_pPlayer2->SetActive(false);
			m_pEnemy->SetActive(true);
			break;
		}
		}
	}
	else if(dae::SceneManager::GetInstance().GetCurrentScene().GetSceneName() == dae::SceneManager::GetInstance().GetScene("highscore").GetSceneName())
	{
		dae::SceneManager::GetInstance().SetActiveScene("mainMenu");
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

