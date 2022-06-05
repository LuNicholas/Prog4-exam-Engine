#include "MiniginPCH.h"
#include "FpsComponent.h"
#include "Font.h"
#include "ResourceManager.h"

dae::FpsComponent::FpsComponent()
	:m_Fps(0)
	, m_pTextComp(nullptr)
{
}
dae::FpsComponent::~FpsComponent()
{
}
void dae::FpsComponent::Init(std::shared_ptr<Font> font)
{
	m_pTextComp = m_pGameObject->AddComponent<TextComponent>();
	m_pTextComp->SetFont(font);
}

void dae::FpsComponent::Update(float deltaTime)
{
	m_Fps = int(1 / deltaTime);
	m_pTextComp->SetText(std::to_string(m_Fps));
}
void dae::FpsComponent::FixedUpdate(float)
{
}

void dae::FpsComponent::Render() const
{
}

