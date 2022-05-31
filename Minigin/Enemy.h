#pragma once
#include "Component.h"

namespace dae
{
	class PeterPepper;
	class MovementComponent;
	class CollisionBox;
	class AnimationManager;

	enum class MoveState
	{
		Up,
		Dowm,
		Left,
		Right
	};

	class Enemy final : public Component
	{
		friend class GameObject;
	public:
		~Enemy();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void Init();
		void AddPlayer(PeterPepper* player);

		void KillEnemy();

	private:
		Enemy();

		void MoveLeft();
		void MoveRight();
		void MoveUp();
		void MoveDown();

		std::vector<PeterPepper*> m_Players;
		int m_PlayerHeightOffset;

		bool m_OnLadder;
		bool m_GoingUp;
		CollisionBox* m_pLastLadder;

		bool m_GoingRight;

		MoveState m_MovementState;

		MovementComponent* m_pMovementComp;
		AnimationManager* m_pAnimationComp;
	};
}
