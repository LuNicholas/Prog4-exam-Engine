#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"


dae::GameObject::GameObject()
	:m_pParent(nullptr)
{

}

dae::GameObject::~GameObject()
{
	for (Component* comp : m_pComponents)
	{
		delete comp;
	}
}

void dae::GameObject::Update(float deltaTime)
{
	for (Component* comp : m_pComponents)
	{
		comp->Update(deltaTime);
	}

	for (GameObject* child : m_pChildren)
	{
		child->Update(deltaTime);
	}
}

void dae::GameObject::FixedUpdate(float deltaTime)
{
	for (Component* comp : m_pComponents)
	{
		comp->FixedUpdate(deltaTime);
	}

	for (GameObject* child : m_pChildren)
	{
		child->FixedUpdate(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	//const auto& pos = m_Transform.GetPosition();
	for (Component* comp : m_pComponents)
	{
		comp->Render();
	}
}

void dae::GameObject::SetParent(GameObject* parent)
{
	m_pParent = parent;
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_pChildren.size();
}

dae::GameObject* dae::GameObject::GetChildAt(int index) const
{
	if (index > int(m_pChildren.size()))
		return nullptr;

	return m_pChildren.at(index);
}

dae::GameObject* dae::GameObject::RemoveChild(int index)
{
	if (index > int(m_pChildren.size()))
		return nullptr;

	auto child = m_pChildren.at(index);
	child->SetParent(nullptr);
	m_pChildren.erase(m_pChildren.begin() + index);
	return child;
}

void dae::GameObject::AddChild(GameObject* go)
{
	go->m_pParent = this;
	m_pChildren.push_back(go);
}


void dae::GameObject::SetPosition(float x, float y)
{
	glm::vec3 oldPos = m_Transform.GetPosition();
	glm::vec3 diff;
	diff.x = oldPos.x - x;
	diff.y = oldPos.y - y;
	
	m_Transform.SetPosition(x, y, 0.0f);

	//move all child positions
	for (GameObject* pChild : m_pChildren)
	{
		glm::vec3 oldChildPos = pChild->m_Transform.GetPosition();
		pChild->SetPosition(oldChildPos.x + diff.x, oldChildPos.y + diff.y);
	}

}
