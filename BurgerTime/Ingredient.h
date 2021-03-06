#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class CollisionBox;
	class Texture2D;

	class Ingredient final : public Component, public Subject
	{
		friend class GameObject;
	public:
		enum class IngredientType
		{
			topBun,
			salad,
			patty,
			tomato,
			cheese,
			botBun,
		};

		~Ingredient();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void Init(IngredientType type, glm::vec2 spawnPos);

		bool IsOnPlate();
		void Reset();
		void SetlleStartPlatform();

		Ingredient(const Ingredient& other) = delete;
		Ingredient(Ingredient&& other) = delete;
		Ingredient& operator=(const Ingredient& other) = delete;
		Ingredient& operator=(Ingredient&& other) = delete;

	private:
		Ingredient();
		std::vector<std::pair<bool, CollisionBox*>> m_CollionBoxes;
		CollisionBox* m_pBigCollisionBox;

		glm::vec2 m_SpawnPos;

		float m_BoxWidth;
		float m_BoxHeight;
		int m_NrOfBoxes;
		int m_FloorOffset;
		bool m_OnPlate;
		int m_WalkedOnOffset;

		CollisionBox* m_CurrentFloor;
		float m_DroppingSpeed;
		bool m_IsDropping;

		bool m_EnemyOnTop;
		int m_ExtraDrops;
		int m_EnemiesOnTop;

		std::shared_ptr<Texture2D> m_Texture{};

		void AllignIngredient();


	};

}