#include "MiniginPCH.h"
#include "Bun.h"
#include "GameObject.h"
#include "CollisionBox.h"
#include "Subject.h"
#include "Events.h"

dae::Bun::Bun()
	:m_IsDropping(true)
	, m_CurrentFloor(nullptr)
	, m_DroppingSpeed(40)
	, m_BoxWidth(18)
	, m_BoxHeight(20)
	, m_NrOfBoxes(5)
	, m_OnPlate(false)
{
	std::shared_ptr<GameObject> m_ColliderGo = std::make_shared<GameObject>();
}
dae::Bun::~Bun()
{
}

void dae::Bun::Init()
{
	glm::vec2 thisPos = m_Transform.GetPosition();

	for (size_t i = 0; i < m_NrOfBoxes; i++)//ADD TEXTURE
	{
		CollisionBox* box = m_pGameObject->AddComponent<CollisionBox>();
		box->SetPosition(thisPos.x + i * m_BoxWidth, thisPos.y);
		box->SetBox(m_BoxWidth, m_BoxHeight);
		box->SetTag("bun");
		m_CollionBoxes.push_back(std::pair(false, box));
	}

	std::vector<CollisionBox*> colliders = m_CollionBoxes.front().second->GetCollidingWith();
	for (CollisionBox* box : colliders)
	{
		if (box->GetTag() == "floor")
		{
			m_CurrentFloor = box;
		}
	}

	//m_pGameObject->AddChild(m_ColliderGo.get());

	//for (size_t i = 0; i < 3; i++)
	//{
	//	CollisionBox* box = colliderGo->AddComponent<CollisionBox>();
	//	box->SetBox(15, 10);
	//	box->SetTag("bun");
	//	box->SetPosition(i * 15, 50);
	//	m_CollionBoxes.push_back(box);
	//}
}

void dae::Bun::Update(float deltaTime)
{
	if (m_OnPlate)
		return;

	if (m_IsDropping)
	{
		glm::vec2 currentPos = m_pGameObject->GetWorldPosition();

		m_pGameObject->SetPosition(currentPos.x, currentPos.y + (m_DroppingSpeed * deltaTime));

		std::vector<CollisionBox*> colliders = m_CollionBoxes.front().second->GetCollidingWith();
		for (CollisionBox* box : colliders)
		{
			if (box->GetTag() == "floor")
			{
				if (box != m_CurrentFloor)
				{
					m_IsDropping = false;
					m_CurrentFloor = box;
					for (std::pair<bool, CollisionBox*>& bunBox : m_CollionBoxes)
					{
						bunBox.first = false;
					}
				}
			}
			else if (box->GetTag() == "bun")
			{
				if (box->GetGameObject()->GetComponent<Bun>()->m_OnPlate)
				{
					m_OnPlate = true;
					m_IsDropping = false;
				}
				else if (box->GetGameObject()->GetComponent<Bun>()->m_IsDropping == false)
				{
					box->GetGameObject()->GetComponent<Bun>()->m_IsDropping = true;
					Notify(*m_pGameObject, Event::BunDropped);
				}

			}
			else if (box->GetTag() == "plate")
			{
				m_OnPlate = true;
				m_IsDropping = false;
			}
		}
		return;
	}


	//check the collision boxs iguess that collide with player(idea only check the outer collision boxes to lessen the checks)
	int nrCollidedBoxes = 0;
	for (std::pair<bool, CollisionBox*>& bunBox : m_CollionBoxes)
	{
		if (bunBox.first == false)
		{
			std::vector<CollisionBox*> colliders = bunBox.second->GetCollidingWith();
			for (CollisionBox* box : colliders)
			{
				if (box->GetTag() == "Player")
				{
					//set those boxes to have been collided
					if (bunBox.second->IsPointInCollider(box->GetPosition() + glm::vec3(box->GetSize().x / 2, box->GetSize().y /2, 0)))//check if middle point of player collides
					{
						bunBox.first = true;
						nrCollidedBoxes++;

					}
				}
			}
		}
		else
		{
			nrCollidedBoxes++;
		}
	}

	//if all have been collided drop till colliding with floor
	if (nrCollidedBoxes == m_CollionBoxes.size())
	{
		m_IsDropping = true;
		Notify(*m_pGameObject, Event::BunDropped);
	}

}
void dae::Bun::FixedUpdate(float deltaTime)
{
}
void dae::Bun::Render() const
{
}


