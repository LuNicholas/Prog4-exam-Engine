#pragma once
#include "TextComponent.h"
#include "Observer.h"

namespace dae
{
	class Font;
	class PlayerUiComponent final : public Component, public Observer
	{
	public:
		friend class GameObject;

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void SetPosition(float x, float y);
		void SetFont(std::shared_ptr<Font> font);
		void SetLives(int lives);
		void SetPeppers(int pepperAmount);
		void SetScore(int score);
		
		void SetVisible(bool visibility);
		void SetScoreVisible(bool visibility);

		void AddScore(int score);
		int GetScore() const;

		~PlayerUiComponent();
		PlayerUiComponent(const PlayerUiComponent& other) = delete;
		PlayerUiComponent(PlayerUiComponent&& other) = delete;
		PlayerUiComponent& operator=(const PlayerUiComponent& other) = delete;
		PlayerUiComponent& operator=(PlayerUiComponent&& other) = delete;


	private:
		void onNotify(const dae::GameObject& go, const Event& event) override;
		PlayerUiComponent();		

		dae::TextComponent* m_pHpText;
		dae::TextComponent* m_pPepperText;
		dae::TextComponent* m_pScoreText;
		int m_score = 0;

		bool m_Visible;
		bool m_ScoreVisible;
	};

}

