#pragma once
#include "Transform.h"


namespace dae
{
	class GameObject;

	class Component abstract
	{
	public:

		virtual ~Component() = default;

		virtual void Update(float deltaTime) = 0;
		virtual void FixedUpdate(float deltaTime) = 0;
		virtual void Render() const = 0;

		void SetPosition(float x, float y) { m_Transform.SetPosition(x, y, 0.0f); };
		glm::vec3 GetPosition() { return m_Transform.GetPosition(); };
		GameObject* GetGameObject() { return m_pGameObject; };


	protected:
		GameObject* m_pGameObject = nullptr;
		dae::Transform m_Transform;

		Component() = default;
	};
}
