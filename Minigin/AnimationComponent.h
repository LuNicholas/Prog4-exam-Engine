#pragma once
#include "Component.h"
#include "Transform.h"

namespace dae
{
	class Texture2D;
	class AnimationComponent final : public Component
	{
	public:
		friend class GameObject;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;


		void SetPosition(float x, float y);
		void SetRowCol(int rows, int cols);
		void SetTexture(std::string filename);
		void SetTextureSize(int w, int h);
		void SetFrameTime(float time);

		~AnimationComponent();
		AnimationComponent(const AnimationComponent& other) = delete;
		AnimationComponent(AnimationComponent&& other) = delete;
		AnimationComponent& operator=(const AnimationComponent& other) = delete;
		AnimationComponent& operator=(AnimationComponent&& other) = delete;

	private:
		AnimationComponent();

		Transform m_Transform;
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
