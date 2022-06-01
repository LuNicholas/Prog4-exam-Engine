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

	for (std::shared_ptr<GameObject> child : m_pChildren)
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

	for (std::shared_ptr<GameObject> child : m_pChildren)
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

	for (std::shared_ptr<GameObject> child : m_pChildren)
	{
		child->Render();
	}
}

//void dae::GameObject::SetParent(GameObject* parent)
//{
//	if (m_pParent != nullptr)
//	{
//		std::vector<GameObject*> parentChildren = m_pParent->m_pChildren;
//		parentChildren.erase(std::remove(parentChildren.begin(), parentChildren.end(), this), parentChildren.end());
//	}
//
//	m_pParent = parent;
//	parent->AddChild(this);
//}

std::shared_ptr<dae::GameObject> dae::GameObject::AddChild()
{
	auto go = std::make_shared<GameObject>();

	go->m_pParent = this;
	m_pChildren.push_back(go);

	return go;
}


dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

size_t dae::GameObject::GetChildCount() const
{
	return m_pChildren.size();
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(int index) const
{
	if (index > int(m_pChildren.size()))
		return nullptr;

	return m_pChildren.at(index);
}

std::shared_ptr<dae::GameObject> dae::GameObject::RemoveChild(int index)
{
	if (index > int(m_pChildren.size()))
		return nullptr;

	auto child = m_pChildren.at(index);
	child->m_pParent = nullptr;
	m_pChildren.erase(m_pChildren.begin() + index);
	return child;
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_PositionIsDirty = true;

	glm::vec3 oldPos = m_Transform.GetPosition();
	glm::vec3 diff;
	diff.x = x - oldPos.x;
	diff.y = y - oldPos.y;

	m_Transform.SetPosition(x, y, 0.0f);

	//move all child positions
	for (std::shared_ptr<GameObject> pChild : m_pChildren)
	{
		if (pChild->m_FollowParent)
		{
			glm::vec3 oldChildPos = pChild->m_Transform.GetPosition();
			pChild->SetPosition(oldChildPos.x + diff.x, oldChildPos.y + diff.y);
		}
	}

	//move all components
	for (Component* pComp : m_pComponents)
	{
		glm::vec3 oldCompPos = pComp->GetPosition();
		pComp->SetPosition(oldCompPos.x + diff.x, oldCompPos.y + diff.y);
	}

}

glm::vec3 dae::GameObject::GetWorldPosition()
{
	if (m_PositionIsDirty)
		UpdateWorldPosition();
	return m_Transform.GetWorldPosition();
}
glm::vec3 dae::GameObject::GetLocalPosition()
{
	return m_Transform.GetPosition();
}
void dae::GameObject::UpdateWorldPosition()
{
	if (m_PositionIsDirty)
	{
		if (m_pParent == nullptr || !m_FollowParent)
			m_Transform.SetWorldPosition(m_Transform.GetPosition());
		else
			m_Transform.SetWorldPosition(m_pParent->m_Transform.GetWorldPosition() + m_Transform.GetPosition());
	}
	m_PositionIsDirty = false;
}
void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_Transform.SetPosition(pos);
	m_PositionIsDirty = true;
}
void dae::GameObject::SetFollowParent(bool followParent)
{
	m_FollowParent = followParent;
}