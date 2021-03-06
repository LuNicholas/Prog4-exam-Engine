#pragma once
#include "Component.h"

class PeterPepper;

namespace dae
{
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

	enum class EnemyType
	{
		bean,
		egg,
		Pickle,
	};

	class Enemy final : public Component
	{
		friend class GameObject;
	public:
		~Enemy();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void Init(EnemyType enemyType, glm::vec2 spawnPoint, float initialSpawnTime);
		void AddPlayer(PeterPepper* player);
		void Pause();
		void Reset();

		void KillEnemy();
		void SetStunned();
		bool GetIsDead();
		EnemyType GetType();
		void SetActive(bool active);

	private:
		Enemy();

		int m_Speed;

		bool m_IsDead;

		bool m_IsStunnned;
		float m_StunTime;
		float m_CurrentStunTime;

		std::vector<PeterPepper*> m_Players;
		int m_PlayerHeightOffset;

		bool m_OnLadder;
		bool m_GoingUp;
		CollisionBox* m_pLastLadder;

		bool m_GoingRight;

		MoveState m_MovementState;

		MovementComponent* m_pMovementComp;
		AnimationManager* m_pAnimationComp;

		glm::vec2 m_SpawnPoint;
		float m_InitialSpawnTime;
		bool m_OnInitialSpawn;
		float m_SpawnTimer;
		float m_DeathTime;
		float m_DissapearTime;
		bool m_Paused;

		bool m_IsActive;

		dae::EnemyType m_Type;
	};
}
