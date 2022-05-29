#include "MiniginPCH.h"
#include "PlayerUiComponent.h"
#include "PeterPepper.h"
#include "Events.h"

dae::PlayerUiComponent::PlayerUiComponent()
{
	m_pHpText = new dae::TextComponent();
	m_pHpText->SetText("0");

	m_pScoreText = new dae::TextComponent();
	m_pScoreText->SetText("score: 0");
}
dae::PlayerUiComponent::~PlayerUiComponent()
{
	delete m_pHpText;
	delete m_pScoreText;

	
}

void dae::PlayerUiComponent::Update(float deltaTime)
{
	m_pHpText->Update(deltaTime);
	m_pScoreText->Update(deltaTime);
}
void dae::PlayerUiComponent::FixedUpdate(float)
{
}

void dae::PlayerUiComponent::Render() const
{
	m_pHpText->Render();
	m_pScoreText->Render();
}

void dae::PlayerUiComponent::SetPosition(float x, float y)
{
	m_pHpText->SetPosition(x, y);
	m_pScoreText->SetPosition(x, y + 30);
}

void dae::PlayerUiComponent::SetFont(std::shared_ptr<Font> font)
{
	m_pHpText->SetFont(font);
	m_pScoreText->SetFont(font);
}

void dae::PlayerUiComponent::SetLives(int lives)
{
	m_pHpText->SetText("lives: " + std::to_string(lives));

}
void dae::PlayerUiComponent::AddScore(int score)
{
	m_score += score;
	m_pScoreText->SetText("score: " + std::to_string(m_score));
}


void dae::PlayerUiComponent::onNotify(const dae::GameObject& go, const Event& event)
{
	switch (event)
	{
	case Event::PlayerHit:
	{
		dae::PeterPepper* peterPepper = go.GetComponent<dae::PeterPepper>();
		if (peterPepper != nullptr)
			SetLives(peterPepper->GetHealth()->GetHealth());
		break;
	}
	case Event::BunDropped:
	{
		AddScore(100);
		break;
	}
	}
}