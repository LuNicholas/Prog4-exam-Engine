#pragma once
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class Enemy;
	class Ingredient;
}
	class Plate;

class GameManager final : public dae::Component, public dae::Observer
{
public:
	friend class dae::GameObject;

	~GameManager();

	void AddEnemy(dae::Enemy* enemy);
	void AddIngredient(dae::Ingredient* ingredient);
	void AddPlate(Plate* plate);
	void SetLevel(std::shared_ptr<dae::GameObject>& level);
	void AddPlayer(std::shared_ptr<dae::GameObject>& player, glm::vec2 playerSpawn);

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
	void ResetPlayers();
	void MoveLevel();

	bool m_GamePaused;
	float m_PauseTime;
	float m_PauseTimer;

	int m_PlayerAmount;
	int m_PlayersDead;

	std::vector<dae::Enemy*> m_Enemies;
	std::vector<dae::Ingredient*> m_Ingredients;
	std::vector<Plate*> m_Plates;
	std::shared_ptr<dae::GameObject> m_pLevel;
	std::vector<std::shared_ptr<dae::GameObject>> m_pPlayers;
	std::vector<glm::vec2> m_SpawnPoints;

	bool m_NextLevel;
	bool m_DoOnce;
};

