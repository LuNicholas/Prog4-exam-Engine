#pragma once
#include "Component.h"

namespace dae
{
	class Texture2D;
	class Transform;
	class SpriteAnimation final
	{
	public:
		SpriteAnimation(const std::string& spriteSheet, int width, int height, int col, int row, float frameTime);

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void SetTransform(const Transform& transform);

		~SpriteAnimation();
		SpriteAnimation(const SpriteAnimation& other) = delete;
		SpriteAnimation(SpriteAnimation&& other) = delete;
		SpriteAnimation& operator=(const SpriteAnimation& other) = delete;
		SpriteAnimation& operator=(SpriteAnimation&& other) = delete;

	private:

		int m_Row = 0;
		int m_Col = 0;

		float m_FrameTime = 0;
		float m_CurrentFrameTime = 0;
		int m_CurrentSprite = 0;

		std::shared_ptr<Texture2D> m_Texture{};
		glm::vec2 m_SizeTexture{};
		glm::vec2 m_Size{};

		Transform m_Transform;

		glm::vec4 GetDestRect() const;
		glm::vec4 GetsrcRect() const;

	};
}
