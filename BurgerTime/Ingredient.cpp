#include "BurgerTimePCH.h"
#include "Ingredient.h"
#include "GameObject.h"
#include "CollisionBox.h"
#include "Subject.h"
#include "Events.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Enemy.h"

dae::Ingredient::Ingredient()
	:m_IsDropping(true)
	, m_CurrentFloor(nullptr)
	, m_DroppingSpeed(80)
	, m_BoxWidth(19)
	, m_BoxHeight(20)
	, m_NrOfBoxes(5)
	, m_OnPlate(false)
	, m_FloorOffset(7)
	, m_WalkedOnOffset(5)
	, m_pBigCollisionBox(nullptr)
	, m_EnemyOnTop(false)
	, m_ExtraDrops(0)
	, m_EnemiesOnTop(0)
{
}
dae::Ingredient::~Ingredient()
{
}

void dae::Ingredient::Init(const std::string& textureFileName)
{
	glm::vec2 thisPos = m_Transform.GetPosition();

	for (size_t i = 0; i < m_NrOfBoxes; i++)//ADD TEXTURE
	{
		CollisionBox* box = m_pGameObject->AddComponent<CollisionBox>();
		box->SetPosition(thisPos.x + i * m_BoxWidth, thisPos.y);
		box->SetBox(m_BoxWidth, m_BoxHeight);
		m_CollionBoxes.push_back(std::pair<bool, CollisionBox*>(false, box));
	}

	m_pBigCollisionBox = m_pGameObject->AddComponent<CollisionBox>();
	m_pBigCollisionBox->SetPosition(thisPos.x, thisPos.y);
	m_pBigCollisionBox->SetBox(m_BoxWidth * m_NrOfBoxes, m_BoxHeight);
	m_pBigCollisionBox->SetTag("bun");

	std::vector<CollisionBox*> colliders = m_pBigCollisionBox->GetCollidingWith();
	for (CollisionBox* box : colliders)
	{
		if (box->GetTag() == "floor")
		{
			m_CurrentFloor = box;
		}
	}
	m_Texture = ResourceManager::GetInstance().LoadTexture(textureFileName);
}


void dae::Ingredient::Update(float deltaTime)
{
	if (m_OnPlate)
		return;

	if (m_IsDropping)
	{
		glm::vec2 currentPos = m_pGameObject->GetWorldPosition();

		m_pGameObject->SetPosition(currentPos.x, currentPos.y + (m_DroppingSpeed * deltaTime));

		std::vector<CollisionBox*> colliders = m_pBigCollisionBox->GetCollidingWith();
		for (CollisionBox* box : colliders)
		{
			if (box->GetTag() == "floor")
			{
				if (box != m_CurrentFloor)
				{
					m_IsDropping = false;
					m_CurrentFloor = box;

					resetIngredient();
					if (m_EnemyOnTop)
					{
						if (m_ExtraDrops < m_EnemiesOnTop)
						{
							m_IsDropping = true;
							m_EnemyOnTop = false;
							m_EnemyOnTop = 0;
						}
						else
						{
							m_ExtraDrops++;
						}
					}

				}
			}
			else if (box->GetTag() == "bun")
			{
				if (box->GetGameObject()->GetComponent<Ingredient>()->m_OnPlate)
				{

					m_OnPlate = true;
					m_IsDropping = false;


				}
				else if (box->GetGameObject()->GetComponent<Ingredient>()->m_IsDropping == false)
				{
					box->GetGameObject()->GetComponent<Ingredient>()->m_IsDropping = true;
					box->GetGameObject()->GetComponent<Ingredient>()->resetIngredient();
					Notify(*m_pGameObject, Event::BunDropped);
				}

			}
			else if (box->GetTag() == "plate")
			{
				m_OnPlate = true;
				m_IsDropping = false;
			}
			else if (box->GetTag() == "enemy")
			{
				if (!box->GetGameObject()->GetComponent<Enemy>()->GetIsDead())
				{

					glm::vec3 boxPos = box->GetPosition();

					if (m_pBigCollisionBox->IsPointInCollider(glm::vec2(boxPos.x + box->GetSize().x / 2, boxPos.y)))//top of enemy getting hit 
					{
						box->GetGameObject()->GetComponent<Enemy>()->KillEnemy();
					}
					else//not the top is getting hit so should be on burger
					{
						box->GetGameObject()->GetComponent<Enemy>()->KillEnemy();
						Notify(*m_pGameObject, Event::EnemySquashed);
						//box->GetGameObject()->SetPosition(boxPos.x, boxPos.y + (m_DroppingSpeed * deltaTime));
						m_EnemyOnTop = true;
						m_EnemiesOnTop++;
					}
				}

			}
		}
		return;
	}


	int nrCollidedBoxes = 0;
	for (std::pair<bool, CollisionBox*>& bunBox : m_CollionBoxes)
	{
		if (bunBox.first == false)
		{
			std::vector<CollisionBox*> colliders = bunBox.second->GetCollidingWith();
			for (CollisionBox* box : colliders)
			{
				if (box->GetTag() == "player")
				{
					//set those boxes to have been collided
					if (bunBox.second->IsPointInCollider(box->GetPosition() + glm::vec3(box->GetSize().x / 2, box->GetSize().y, 0)))//check if middle point of player collides
					{
						bunBox.first = true;
						bunBox.second->SetPosition(bunBox.second->GetPosition().x, bunBox.second->GetPosition().y + m_WalkedOnOffset);
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
void dae::Ingredient::FixedUpdate(float deltaTime)
{
}
void dae::Ingredient::Render() const
{
	for (size_t i = 0; i < m_CollionBoxes.size(); i++)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, m_CollionBoxes.at(i).second->GetBox(), glm::vec4(m_BoxWidth * i, 0, m_BoxWidth, m_BoxHeight));
	}

}

void dae::Ingredient::resetIngredient()
{
	for (std::pair<bool, CollisionBox*>& bunBox : m_CollionBoxes)
	{
		if (bunBox.first == true)
		{
			bunBox.first = false;
		}
		else
		{
			bunBox.second->SetPosition(bunBox.second->GetPosition().x, bunBox.second->GetPosition().y + m_WalkedOnOffset);
		}
	}
	m_pBigCollisionBox->SetPosition(m_pBigCollisionBox->GetPosition().x, m_pBigCollisionBox->GetPosition().y + m_WalkedOnOffset);
}

bool dae::Ingredient::IsOnPlate()
{
	return m_OnPlate;
}
