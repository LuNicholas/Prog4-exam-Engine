#pragma once
#include "GameObject.h"


namespace dae
{
	class Font;
	class Texture2D;
	class Transform;

	class TextComponent final : public Component
	{
	public:
		friend class GameObject;
		friend class FpsComponent;
		friend class PlayerUiComponent;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		void SetFont(std::shared_ptr<Font> font) { m_Font = font; };

		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;


	private:
		TextComponent();

		bool m_NeedsUpdate;
		std::string m_Text;
		Transform m_Transform;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
	};
}
