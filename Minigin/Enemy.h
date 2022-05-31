#pragma once
#include "Component.h"

namespace dae
{
	class PeterPepper;
	class CollisionBox;

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

		bool m_OnLadder;
		bool m_GoingUp;
		CollisionBox* m_CurrentLadder;
	};
}
