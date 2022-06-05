#include "BurgerTimePCH.h"
#include "PlayerUiComponent.h"
#include "PeterPepper.h"
#include "Events.h"

dae::PlayerUiComponent::PlayerUiComponent()
	:m_Visible(true)
	, m_ScoreVisible(true)
	, m_TextPosition(0, 0)
{
	//m_pHpText = new dae::TextComponent();
	//m_pHpText->SetText("4");

	//m_pPepperText = new dae::TextComponent();
	//m_pPepperText->SetText("5");

	//m_pScoreText = new dae::TextComponent();
	//m_pScoreText->SetText("0");
}
dae::PlayerUiComponent::~PlayerUiComponent()
{
	//delete m_pHpText;
	//delete m_pPepperText;
	//delete m_pScoreText;
}
void dae::PlayerUiComponent::Init(std::shared_ptr<Font> font, int health)
{
	m_pHpText = m_pGameObject->AddComponent<dae::TextComponent>();
	m_pHpText->SetText(std::to_string(health));
	m_pHpText->SetFont(font);

	m_pPepperText = m_pGameObject->AddComponent<dae::TextComponent>();
	m_pPepperText->SetText("5");
	m_pPepperText->SetFont(font);

	m_pScoreText = m_pGameObject->AddComponent<dae::TextComponent>();
	m_pScoreText->SetText("0");
	m_pScoreText->SetFont(font);
}

void dae::PlayerUiComponent::Update(float deltaTime)
{
	if (!m_Visible)
		return;

}
void dae::PlayerUiComponent::FixedUpdate(float)
{
	if (!m_Visible)
		return;
}

void dae::PlayerUiComponent::Render() const
{
	if (!m_Visible)
		return;

	//m_pHpText->Render();
	//m_pPepperText->Render();
	//if(m_ScoreVisible)
	//	m_pScoreText->Render();
}

void dae::PlayerUiComponent::SetPositionUi(float x, float y)
{
	m_TextPosition = glm::vec2(x, y);
	m_pHpText->SetPosition(x, y);
	m_pPepperText->SetPosition(x - 50, y);
	m_pScoreText->SetPosition(x - 150, y);
}

void dae::PlayerUiComponent::SetFont(std::shared_ptr<Font> font)
{
	m_pHpText->SetFont(font);
	m_pPepperText->SetFont(font);
	m_pScoreText->SetFont(font);
}

void dae::PlayerUiComponent::SetLives(int lives)
{
	m_pHpText->SetText(std::to_string(lives));
}
void dae::PlayerUiComponent::SetPeppers(int pepperAmount)
{
	m_pPepperText->SetText(std::to_string(pepperAmount));
}
void dae::PlayerUiComponent::AddScore(int score)
{
	m_score += score;
	m_pScoreText->SetText(std::to_string(m_score));
}


void dae::PlayerUiComponent::onNotify(const dae::GameObject& go, const Event& event)
{
	if (!m_Visible)
		return;

	switch (event)
	{
	case Event::BunDropped:
	{
		AddScore(50);
		break;
	}
	case Event::BeanKilled:
	{
		AddScore(100);
		break;
	}
	case Event::PickleKilled:
	{
		AddScore(200);
		break;
	}
	case Event::EggKilled:
	{
		AddScore(300);
		break;
	}
	case Event::BunDropped1:
	{
		AddScore(500);
		break;
	}
	case Event::BunDropped2:
	{
		AddScore(1000);
		break;
	}
	case Event::BunDropped3:
	{
		AddScore(2000);
		break;
	}
	case Event::BunDropped4:
	{
		AddScore(4000);
		break;
	}
	case Event::BunDropped5:
	{
		AddScore(8000);
		break;
	}
	case Event::BunDropped6:
	{
		AddScore(16000);
		break;
	}
	}
}
void dae::PlayerUiComponent::SetVisible(bool visibility)
{
	m_Visible = visibility;
	if (visibility)
	{
		m_pHpText->SetPosition(m_TextPosition.x, m_TextPosition.y);
		m_pPepperText->SetPosition(m_TextPosition.x - 50, m_TextPosition.y);
		if(m_ScoreVisible)
			m_pScoreText->SetPosition(m_TextPosition.x - 250, m_TextPosition.y);
		else
			m_pScoreText->SetPosition(-1000, -1000);
	}
	else
	{
		m_pHpText->SetPosition(-1000,-1000);
		m_pPepperText->SetPosition(-1000,-1000);
		m_pScoreText->SetPosition(-1000,-1000);
	}
}

void dae::PlayerUiComponent::SetScore(int score)
{
	m_score = score;
	m_pScoreText->SetText(std::to_string(m_score));
}
void dae::PlayerUiComponent::SetScoreVisible(bool visibility)
{
	m_ScoreVisible = visibility;
}
int dae::PlayerUiComponent::GetScore() const
{
	return m_score;
}