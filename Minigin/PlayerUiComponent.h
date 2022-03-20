#pragma once
#include "TextComponent.h"
#include "Observer.h"

namespace dae
{
	class Font;
	class PlayerUiComponent : public Component, public Observer
	{
	public:
		friend class GameObject;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void SetPosition(float x, float y);
		void SetFont(std::shared_ptr<Font> font);
		void SetLives(int lives);

		void AddScore(int score);

		~PlayerUiComponent();
		PlayerUiComponent(const PlayerUiComponent& other) = delete;
		PlayerUiComponent(PlayerUiComponent&& other) = delete;
		PlayerUiComponent& operator=(const PlayerUiComponent& other) = delete;
		PlayerUiComponent& operator=(PlayerUiComponent&& other) = delete;


	private:
		void onNotify(const dae::GameObject& go, Event event);
		PlayerUiComponent();

		dae::TextComponent* m_pHpText;
		dae::TextComponent* m_pScoreText;
		int m_score = 0;
	};

}

