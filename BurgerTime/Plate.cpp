#include "BurgerTimePCH.h"
#include "Plate.h"
#include "GameObject.h"
#include "CollisionBox.h"
#include "Ingredient.h"


Plate::Plate()
	:m_pCollider(nullptr)
	, m_PlateDone(false)
{
}
Plate::~Plate()
{
}

void Plate::Init(glm::vec2 pos)
{
	m_SpawnPos = pos;
	m_pGameObject->SetPosition(pos.x, pos.y);
	m_pCollider = m_pGameObject->AddComponent<dae::CollisionBox>();
	m_pCollider->SetTag("plate");
	m_pCollider->SetBox(100, 10);
}
void Plate::AddIngredient(dae::Ingredient* ingredient)
{
	m_Ingredients.push_back(ingredient);
}

void Plate::Update(float deltaTime)
{
	if (m_PlateDone)
	{
		return;
	}

	for (dae::Ingredient* ingredient : m_Ingredients)
	{
		if (!ingredient->IsOnPlate())
		{
			return;
		}
	}

	m_PlateDone = true;
}
void Plate::FixedUpdate(float deltaTime)
{
}
void Plate::Render() const
{
}
bool Plate::IsPlateDone() const
{
	return m_PlateDone;
}
void Plate::Reset()
{
	m_pGameObject->SetPosition(m_SpawnPos.x, m_SpawnPos.y);
}