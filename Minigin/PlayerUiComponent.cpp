#include "MiniginPCH.h"
#include "PlayerUiComponent.h"

dae::PlayerUiComponent::PlayerUiComponent()
{
	m_pTextComp = new dae::TextComponent();
	m_pTextComp->SetText("3");
}
dae::PlayerUiComponent::~PlayerUiComponent()
{
	delete m_pTextComp;
}

void dae::PlayerUiComponent::Update(float deltaTime)
{
	m_pTextComp->Update(deltaTime);
}
void dae::PlayerUiComponent::FixedUpdate(float)
{
}

void dae::PlayerUiComponent::Render() const
{
	m_pTextComp->Render();
}

void dae::PlayerUiComponent::SetPosition(float x, float y)
{
	m_pTextComp->SetPosition(x, y);
}

void dae::PlayerUiComponent::SetFont(std::shared_ptr<Font> font)
{
	m_pTextComp->SetFont(font);
}
