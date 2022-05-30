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
	//get peter pepper component and move like that 
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

	//dae::CollisionBox* pCollider = m_actor->GetComponent<dae::CollisionBox>();
	//auto collidingWith = pCollider->GetCollidingWith();

	//for (dae::CollisionBox* pColliding : collidingWith)
	//{
	//	if (pColliding->GetTag() == "floor")
	//	{
	//		//todo
	//		//use peterpepper to move i guess

	//		if (pColliding->IsPointInCollider(glm::vec2(pCollider->GetPosition().x + pCollider->GetSize().x, pCollider->GetPosition().y + pCollider->GetSize().y)))
	//		{
	//			glm::vec3 currentPos = m_actor->GetWorldPosition();
	//			currentPos.x += 1;
	//			m_actor->SetPosition(currentPos.x, currentPos.y);
	//			m_actor->GetComponent<dae::AnimationManager>()->SetActiveAnimation("right");
	//			break;
	//		}
	//	}

	//}



	//dae::PeterPepper* character = m_actor->GetComponent<dae::PeterPepper>();


	//glm::vec3 currentPos = m_actor->GetWorldPosition();
	//currentPos.x += 1;
	//m_actor->SetPosition(currentPos.x, currentPos.y);
}

MoveUp::MoveUp(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void MoveUp::Execute()
{
	dae::CollisionBox* pCollider = m_actor->GetComponent<dae::CollisionBox>();
	auto collidingWith = pCollider->GetCollidingWith();

	for (dae::CollisionBox* pColliding : collidingWith)
	{
		if (pColliding->GetTag() == "Ladder")
		{
			//glm::vec3 currentPos = m_actor->GetWorldPosition();
			//currentPos.y -= 1;
			//m_actor->SetPosition(currentPos.x, currentPos.y);
			//break;


			if (pColliding->IsPointInCollider(glm::vec2(pCollider->GetPosition().x + pCollider->GetSize().x / 2, pCollider->GetPosition().y)))
			{
				glm::vec3 currentPos = m_actor->GetWorldPosition();
				currentPos.y -= 1;
				m_actor->SetPosition(currentPos.x, currentPos.y);
				m_actor->GetComponent<dae::AnimationManager>()->SetActiveAnimation("up");
				break;
			}
		}
	}
}
MoveDown::MoveDown(std::shared_ptr<dae::GameObject> actor)
	:m_actor(actor)
{

}
void MoveDown::Execute()
{
	dae::CollisionBox* pCollider = m_actor->GetComponent<dae::CollisionBox>();
	auto collidingWith = pCollider->GetCollidingWith();

	for (dae::CollisionBox* pColliding : collidingWith)
	{
		if (pColliding->GetTag() == "Ladder")
		{
			//todo
			//use peterpepper to move i guess


			//glm::vec3 currentPos = m_actor->GetWorldPosition();
			//currentPos.y += 1;
			//m_actor->SetPosition(currentPos.x, currentPos.y);
			//break;


			if (pColliding->IsPointInCollider(glm::vec2(pCollider->GetPosition().x + pCollider->GetSize().x / 2, pCollider->GetPosition().y + pCollider->GetSize().y)))
			{
				glm::vec3 currentPos = m_actor->GetWorldPosition();
				currentPos.y += 1;
				m_actor->SetPosition(currentPos.x, currentPos.y);
				m_actor->GetComponent<dae::AnimationManager>()->SetActiveAnimation("forward");
				break;
			}
		}

	}
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