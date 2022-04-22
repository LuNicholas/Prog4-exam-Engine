#pragma once
#include "Transform.h"

class Component abstract
{
public:

	virtual ~Component() = default;

	virtual void Update(float deltaTime) = 0;
	virtual void FixedUpdate(float deltaTime) = 0;
	virtual void Render() const = 0;

	virtual void SetPosition(float x, float y) { m_Transform.SetPosition(x, y, 0.0f); };
	virtual glm::vec3 GetPosition() { return m_Transform.GetPosition(); };

protected:
	dae::Transform m_Transform;

	Component() = default;
};

