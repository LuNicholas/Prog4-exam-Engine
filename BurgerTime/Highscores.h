#pragma once
#include "Component.h"
#include <iostream>
#include <fstream>
#include <iomanip> 
#include "TextComponent.h"


namespace dae
{
	class PlayerUiComponent;
	class PeterPepper;



	class Highscores final : public dae::Component
	{
	public:
		friend class dae::GameObject;

		~Highscores();

		void Update(float deltaTime);
		void FixedUpdate(float deltaTime);
		void Render() const;

		void Init(std::shared_ptr<dae::GameObject>& player, std::shared_ptr<dae::Font> font);

		Highscores(const Highscores& other) = delete;
		Highscores(Highscores&& other) = delete;
		Highscores& operator=(const Highscores& other) = delete;
		Highscores& operator=(Highscores&& other) = delete;

	private:
		Highscores();


		std::vector<dae::TextComponent*> m_HighscoresText;

		dae::TextComponent* m_PlayerScoreText;

		std::string m_FileName;
		std::vector<int> m_Highscores;

		std::shared_ptr<dae::GameObject> m_PlayerGo;
		int m_PlayerScore;

		bool m_DoOnce;
	};

}