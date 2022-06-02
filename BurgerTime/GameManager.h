#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class Enemy;
	class Ingredient;
}

class GameManager : public dae::Component, public dae::Observer
{
public:
	friend class dae::GameObject;

	~GameManager();

	void AddEnemy(dae::Enemy* enemy);

	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);
	void Render() const;

	GameManager(const GameManager& other) = delete;
	GameManager(GameManager&& other) = delete;
	GameManager& operator=(const GameManager& other) = delete;
	GameManager& operator=(GameManager&& other) = delete;

private:
	void onNotify(const dae::GameObject& go, const Event& event) override;
	GameManager();

	void Pause();
	void Reset();
	void FullReset();

	bool m_GamePaused;
	float m_PauseTime = 2.f;
	float m_PauseTimer = 0;

	std::vector<dae::Enemy*> m_Enemies;
	std::vector<dae::Ingredient*> m_Ingredients;
};

