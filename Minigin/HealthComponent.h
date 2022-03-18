#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class HealthComponent final : public Component, public Subject
	{
	public:
		friend class GameObject;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		int GetHealth();
		void SetHealth(int health);
		void DealDamage(int damage, const GameObject& hitGameObject);

		~HealthComponent();
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

	private:
		HealthComponent();

		int m_currentHealth = 0;
	};
}

