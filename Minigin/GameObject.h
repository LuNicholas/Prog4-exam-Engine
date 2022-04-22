#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class Texture2D;

	class GameObject final : public SceneObject, public Subject
	{

	public:
		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		template <typename T>
		T* AddComponent(T* component);

		template <typename T>
		T* AddComponent();

		template <typename T>
		T* GetComponent() const;

		template <typename T>
		void RemoveComponent(T* component);

		void SetParent(GameObject* parent);
		GameObject* GetParent() const;

		size_t GetChildCount() const;
		GameObject* GetChildAt(int index) const;
		GameObject* RemoveChild(int index);
		void AddChild(GameObject* go);


		void SetPosition(float x, float y);
		glm::vec3 GetWorldPosition();
		glm::vec3 GetLocalPosition();

		GameObject();
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<GameObject*> m_pChildren;
		GameObject* m_pParent;

		std::vector<Component*> m_pComponents;

		Transform m_Transform;
		bool m_positionIsDirty = true;


		void UpdateWorldPosition();
		void SetLocalPosition(const glm::vec3& pos);

	};
}


template <class T>
T* dae::GameObject::AddComponent(T* component)
{

	if (typeid(Component*) == typeid(dynamic_cast<Component*>(component)))
	{
		m_pComponents.push_back((Component*)(component));
		return component;
	}

	return nullptr;
}

template <class T>
T* dae::GameObject::AddComponent()
{
	if (std::is_base_of<Component, T>::value)
	{
		T* pComponent = new T();
		pComponent->SetPosition(m_Transform.GetPosition().x, m_Transform.GetPosition().y);
		m_pComponents.push_back(pComponent);
		return pComponent;
	}

	return nullptr;
}

template <class T>
T* dae::GameObject::GetComponent() const
{
	for (Component* comp : m_pComponents)
	{
		if (typeid(*comp) == typeid(T))
			return dynamic_cast<T*>(comp);
	}

	return nullptr;
}

template <class T>
void dae::GameObject::RemoveComponent(T* component)
{
	for (Component* comp : m_pComponents)
	{
		if (comp == component)
			m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), component), m_pComponents.end());
	}
}