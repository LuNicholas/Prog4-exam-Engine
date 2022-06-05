#pragma once
#include <Component.h>
#include "Subject.h"	

namespace dae
{
	class CollisionBox;
	class MovementComponent;
	class AnimationManager;
}
class PeterPepper;

class EnemyPlayer final : public dae::Component, public dae::Subject
{


public:
	friend class dae::GameObject;

	~EnemyPlayer();

	void Init(PeterPepper* player);

	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);
	void Render() const;

	void Kill();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void IdleForward();
	void IdleUp();

	void SetActive(bool active);
	bool GetIsActive() const;
	bool GetIsDead() const;
	void SetSpawn(const glm::vec2& spawnPos);

	void SetStunned(bool stunned);
	void SetPaused(bool paused);

	EnemyPlayer(const EnemyPlayer& other) = delete;
	EnemyPlayer(EnemyPlayer&& other) = delete;
	EnemyPlayer& operator=(const EnemyPlayer& other) = delete;
	EnemyPlayer& operator=(EnemyPlayer&& other) = delete;

private:
	EnemyPlayer();

	PeterPepper* m_pPlayer;

	dae::CollisionBox* m_pCollisionBox;
	dae::CollisionBox* m_pPlayerCollisionBox;


	dae::MovementComponent* m_pMovementComp;
	float m_MoveSpeed;

	dae::AnimationManager* m_pAnimationComp;

	int m_Width;
	int m_Height;

	glm::vec2 m_SpawnPos;

	bool m_Paused;
	bool m_IsActive;

	bool m_Stunned;
	float m_StunTime;
	float m_StunTimer;

	bool m_Dead;
	float m_DeathTime;
	float m_DeathTimer;
};

