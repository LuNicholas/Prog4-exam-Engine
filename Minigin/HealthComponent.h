#pragma once
#include "Component.h"

namespace dae
{
	class HealthComponent final : public Component
	{
	public:
		friend class GameObject;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		int GetHealth();
		void SetHealth(int health);
		void DealDamage(int damage);

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

