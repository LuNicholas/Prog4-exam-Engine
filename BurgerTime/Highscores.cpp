#include "BurgerTimePCH.h"
#include "Highscores.h"
#include "GameObject.h"
#include "PlayerUiComponent.h"

dae::Highscores::Highscores()
	:m_FileName("../Data/Highscores.txt")
	, m_DoOnce(false)
	, m_PlayerScore(-1)
	, m_PlayerScoreText(nullptr)
{

}
dae::Highscores::~Highscores()
{
}

void dae::Highscores::Init(std::shared_ptr<dae::GameObject>& player, std::shared_ptr<dae::Font> font)
{


	for (size_t i = 0; i < 5; i++)
	{
		m_HighscoresText.push_back(m_pGameObject->AddComponent<dae::TextComponent>());
	}

	m_PlayerScoreText = m_pGameObject->AddComponent<dae::TextComponent>();


	glm::vec2 pos(300, 100);
	for (auto& text : m_HighscoresText)
	{
		text->SetPosition(pos.x, pos.y);
		pos.y += 35;
		text->SetText("0");
		text->SetFont(font);
	}
	m_PlayerScoreText->SetPosition(pos.x, pos.y + 100);
	m_PlayerScoreText->SetText("0");
	m_PlayerScoreText->SetFont(font);


	m_PlayerGo = player;



	std::ifstream input;
	input.open(m_FileName, std::ios::in | std::ios::binary);

	std::string line;
	if (input.is_open())
	{
		while (!input.eof())
		{
			std::getline(input, line);
			if (!line.empty())
				m_Highscores.push_back(std::stoi(line));
		}
	}
}

void dae::Highscores::Update(float deltaTime)
{
	//check if player score is different
	int playerScore = m_PlayerGo->GetChildAt(1)->GetComponent<dae::PlayerUiComponent>()->GetScore();

	if (m_PlayerScore != playerScore)
	{
		m_PlayerScore = playerScore;
		m_PlayerScoreText->SetText(std::to_string(playerScore));

		for (int& score : m_Highscores)
		{
			if (playerScore > score)
			{
				int temp = score;
				score = playerScore;
				playerScore = temp;
			}
		}

		for (size_t i = 0; i < m_HighscoresText.size(); i++)
		{
			m_HighscoresText.at(i)->SetText(std::to_string(m_Highscores.at(i)));
		}


		std::ofstream output(m_FileName, std::ios::trunc);

		for (int& score : m_Highscores)
		{
			output << score;
			output << '\n';
		}


		m_PlayerGo->GetChildAt(1)->GetComponent<dae::PlayerUiComponent>()->SetScore(0);
		m_PlayerScore = 0;
	}
}
void dae::Highscores::FixedUpdate(float deltaTime)
{
}
void dae::Highscores::Render() const
{
	glm::vec2 pos(314, 100);

	for (const auto& text : m_HighscoresText)
	{
		text->SetPosition(pos.x, pos.y);
		pos.y += 35;
	}

	m_PlayerScoreText->SetPosition(pos.x, pos.y + 100);
	m_PlayerScoreText->Render();
}