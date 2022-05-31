#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class CollisionBox;
	class Texture2D;
	class Bun final : public Component, public Subject
	{
		friend class GameObject;
	public:
		~Bun();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void Init(const std::string& textureFileName);

		Bun(const Bun& other) = delete;
		Bun(Bun&& other) = delete;
		Bun& operator=(const Bun& other) = delete;
		Bun& operator=(Bun&& other) = delete;

	private:
		Bun();
		std::vector<std::pair<bool, CollisionBox*>> m_CollionBoxes;
		CollisionBox* m_pBigCollisionBox;

		float m_BoxWidth;
		float m_BoxHeight;
		int m_NrOfBoxes;
		int m_FloorOffset;
		bool m_OnPlate;
		int m_WalkedOnOffset;

		CollisionBox* m_CurrentFloor;
		float m_DroppingSpeed;
		bool m_IsDropping;

		std::shared_ptr<Texture2D> m_Texture{};

		void resetIngredient();
	};

}