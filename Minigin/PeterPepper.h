#pragma once
#include "Component.h"
#include "Health.h"

namespace dae
{
	class MovementComponent;
	class CollisionBox;
	class AnimationManager;

	class PeterPepper : public Component
	{
		enum class LastLookDir
		{
			Up,
			Dowm,
			Left,
			Right
		};

	public:
		friend class GameObject;

		void Init();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void Pepper();

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

		Health* m_pHealth;


		MovementComponent* m_pMovementComp;
		AnimationManager* m_pAnimationComp;


		CollisionBox* m_pCollisionBox;
		int m_WidthPlayer;
		int m_HeightPlayer;

		float m_MoveSpeed;
		LastLookDir m_LastLookingDirection;

	};
}
