#pragma once
#include "Component.h"

namespace dae
{
	class CollisionBox : public Component
	{
	public:
		friend class GameObject;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void SetBox(int width, int height);
		void SetTag(const std::string& tag);
		std::string GetTag();

		std::vector<CollisionBox*> GetCollidingWith();
		bool IsOverlappingWith(CollisionBox* collider);
		bool IsPointInCollider(const glm::vec2& point);
		glm::vec2 GetSize();
		glm::vec4 GetBox();

		~CollisionBox();
		CollisionBox(const CollisionBox& other) = delete;
		CollisionBox(CollisionBox&& other) = delete;
		CollisionBox& operator=(const CollisionBox& other) = delete;
		CollisionBox& operator=(CollisionBox&& other) = delete;

	private:
		CollisionBox();
		void DrawBox() const;

		static std::vector<CollisionBox*> m_CollisionBoxes;

		int m_Width;
		int m_Height;
		std::string m_Tag;
	};
}
