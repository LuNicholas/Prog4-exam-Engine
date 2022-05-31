#pragma once
#include "Component.h"

namespace dae
{
	class CollisionBox;

	class MovementComponent final : public Component
	{
		friend class GameObject;
	public:
		~MovementComponent();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void SetMovementBox(CollisionBox* collision);
		void SetSpeed(float speed);

		bool MoveUp();
		bool MoveDown();
		bool MoveLeft();
		bool MoveRight();

		bool OnPlatform();
		bool TouchingLadder();

		CollisionBox* GetLastLadder();

	private:
		MovementComponent();

		int m_FloorOffset;
		float m_Speed;

		CollisionBox* m_pCollisionBox;

		CollisionBox* m_pLastLadder;
	};
}