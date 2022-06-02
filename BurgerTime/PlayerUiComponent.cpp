#include "BurgerTimePCH.h"
#include "PlayerUiComponent.h"
#include "PeterPepper.h"
#include "Events.h"

dae::PlayerUiComponent::PlayerUiComponent()
{
	m_pHpText = new dae::TextComponent();
	m_pHpText->SetText("4");

	m_pPepperText = new dae::TextComponent();
	m_pPepperText->SetText("5");

	m_pScoreText = new dae::TextComponent();
	m_pScoreText->SetText("0");
}
dae::PlayerUiComponent::~PlayerUiComponent()
{
	delete m_pHpText;
	delete m_pPepperText;
	delete m_pScoreText;
}

void dae::PlayerUiComponent::Update(float deltaTime)
{
	m_pHpText->Update(deltaTime);
	m_pPepperText->Update(deltaTime);
	m_pScoreText->Update(deltaTime);
}
void dae::PlayerUiComponent::FixedUpdate(float)
{
}

void dae::PlayerUiComponent::Render() const
{
	m_pHpText->Render();
	m_pPepperText->Render();
	m_pScoreText->Render();
}

void dae::PlayerUiComponent::SetPosition(float x, float y)
{
	m_pHpText->SetPosition(x, y);
	m_pPepperText->SetPosition(x-50, y);
	m_pScoreText->SetPosition(x-150, y);
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
	switch (event)
	{
	case Event::PlayerHit:
	{
		PeterPepper* peterPepper = go.GetComponent<PeterPepper>();
		if (peterPepper != nullptr)
			SetLives(peterPepper->GetHealth()->GetHealth());
		break;
	}
	case Event::BunDropped:
	{
		AddScore(100);
		break;
	}
	case Event::EnemySquashed:
	{
		AddScore(200);
		break;
	}
	case Event::PepperUse:
	{

		SetPeppers(go.GetComponent<PeterPepper>()->GetPeppers());
	}
	}
}