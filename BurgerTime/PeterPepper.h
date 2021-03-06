#pragma once
#include "Component.h"
#include "Health.h"

namespace dae
{
	class MovementComponent;
	class CollisionBox;
	class AnimationManager;

}

class PeterPepper final : public dae::Component, public dae::Subject
{
	enum class LastLookDir
	{
		Up,
		Dowm,
		Left,
		Right
	};

public:

	friend class dae::GameObject;

	void Init(const glm::vec2& spawnPos, int health, int peppers);

	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);
	void Render() const;

	void Pepper();
	void Kill();
	void Reset();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void IdleForward();
	void IdleUp();

	dae::Health* GetHealth() const;
	int GetPeppers() const;
	void SetActive(bool activity);
	bool GetActive()const;
	bool IsDead()const;

	void SetSpawn(glm::vec2 spawnPoint);
	void MoveToSpawn();

	~PeterPepper();
	PeterPepper(const PeterPepper& other) = delete;
	PeterPepper(PeterPepper&& other) = delete;
	PeterPepper& operator=(const PeterPepper& other) = delete;
	PeterPepper& operator=(PeterPepper&& other) = delete;

private:
	PeterPepper();

	dae::Health* m_pHealth;
	int m_Health;

	dae::MovementComponent* m_pMovementComp;
	dae::AnimationManager* m_pAnimationComp;

	glm::vec2 m_SpawnPos;

	dae::CollisionBox* m_pCollisionBox;
	int m_WidthPlayer;
	int m_HeightPlayer;

	float m_MoveSpeed;
	LastLookDir m_LastLookingDirection;

	bool m_GotHit;
	bool m_IsDead;

	float m_PauseTime = 2.f;
	float m_PauseTimer = 0;

	int m_Peppers;

	bool m_IsActive;
};

