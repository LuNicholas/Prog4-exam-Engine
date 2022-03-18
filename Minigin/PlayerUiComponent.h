#pragma once
#include "TextComponent.h"


namespace dae
{
	class Font;
	class PlayerUiComponent : public Component
	{
	public:
		friend class GameObject;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void SetPosition(float x, float y);
		void SetFont(std::shared_ptr<Font> font);
		void SetLives(int lives) { m_pTextComp->SetText("lives: " + std::to_string(lives)); }

		~PlayerUiComponent();
		PlayerUiComponent(const PlayerUiComponent& other) = delete;
		PlayerUiComponent(PlayerUiComponent&& other) = delete;
		PlayerUiComponent& operator=(const PlayerUiComponent& other) = delete;
		PlayerUiComponent& operator=(PlayerUiComponent&& other) = delete;

	private:
		PlayerUiComponent();

		dae::TextComponent* m_pTextComp;
	};

}

