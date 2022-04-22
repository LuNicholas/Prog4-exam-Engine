#pragma once
#include "Component.h"

namespace dae
{
	class Texture2D;
	class SpriteAnimationComponent final : public Component
	{
	public:
		friend class GameObject;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;


		void SetRowCol(int rows, int cols);
		void SetTexture(std::string filename);
		void SetTextureSize(int w, int h);
		void SetFrameTime(float time);

		~SpriteAnimationComponent();
		SpriteAnimationComponent(const SpriteAnimationComponent& other) = delete;
		SpriteAnimationComponent(SpriteAnimationComponent&& other) = delete;
		SpriteAnimationComponent& operator=(const SpriteAnimationComponent& other) = delete;
		SpriteAnimationComponent& operator=(SpriteAnimationComponent&& other) = delete;

	private:
		SpriteAnimationComponent();

		int m_Row = 0;
		int m_Col = 0;

		float m_FrameTime = 0;
		float m_CurrentFrameTime = 0;
		int m_CurrentSprite = 0;

		std::shared_ptr<Texture2D> m_Texture{};
		glm::vec2 m_SizeTexture{};
		glm::vec2 m_Size{};

		glm::vec4 GetDestRect() const;
		glm::vec4 GetsrcRect() const;

	};
}
