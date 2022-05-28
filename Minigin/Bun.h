#pragma once
#include "Component.h"

namespace dae
{
	class CollisionBox;

	class Bun : public Component
	{
		friend class GameObject;
	public:
		~Bun();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void Init();

		Bun(const Bun& other) = delete;
		Bun(Bun&& other) = delete;
		Bun& operator=(const Bun& other) = delete;
		Bun& operator=(Bun&& other) = delete;

	private:
		Bun();
		std::shared_ptr<GameObject> m_ColliderGo;
		std::vector<std::pair<bool, CollisionBox*>> m_CollionBoxes;
		float m_BoxWidth;
		float m_BoxHeight;
		int m_NrOfBoxes;

		CollisionBox* m_CurrentFloor;
		float m_DroppingSpeed;
		bool m_IsDropping;
	};

}