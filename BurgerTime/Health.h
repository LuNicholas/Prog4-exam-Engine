#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class Health final : public Subject
	{
	public:
		friend class GameObject;
		Health(int startHealth);
		~Health();

		int GetHealth() const;
		void SetHealth(int health);
		void DealDamage(int damage, const GameObject& hitGameObject);

		Health(const Health& other) = delete;
		Health(Health&& other) = delete;
		Health& operator=(const Health& other) = delete;
		Health& operator=(Health&& other) = delete;

	private:

		int m_currentHealth = 0;
	};
}

