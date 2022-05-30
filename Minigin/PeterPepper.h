#pragma once
#include "Component.h"
#include "Health.h"

namespace dae
{
	class PeterPepper : public Component
	{
	public:
		friend class GameObject;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void MoveLeft();
		void MoveRight();
		void MoveUp();
		void MoveDown();
		void IdleForward();
		void IdleUp();

		dae::Health* GetHealth() const;

		~PeterPepper();
		PeterPepper(const PeterPepper& other) = delete;
		PeterPepper(PeterPepper&& other) = delete;
		PeterPepper& operator=(const PeterPepper& other) = delete;
		PeterPepper& operator=(PeterPepper&& other) = delete;

	private:
		PeterPepper();

		dae::Health* m_pHealth;

		float m_MoveSpeed;

	};
}
