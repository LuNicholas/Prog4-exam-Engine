#pragma once
#include "TextComponent.h"

namespace dae
{
	class Font;
	class FpsComponent final : public Component
	{
	public:
		friend class GameObject;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void SetPosition(float x, float y);
		void SetFont(std::shared_ptr<Font> font);


		~FpsComponent();
		FpsComponent(const FpsComponent& other) = delete;
		FpsComponent(FpsComponent&& other) = delete;
		FpsComponent& operator=(const FpsComponent& other) = delete;
		FpsComponent& operator=(FpsComponent&& other) = delete;

	private:
		FpsComponent();


		int m_Fps;
		dae::TextComponent* m_pTextComp;
	};

}