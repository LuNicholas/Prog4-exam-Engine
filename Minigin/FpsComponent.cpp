#include "MiniginPCH.h"
#include "FpsComponent.h"
#include "Font.h"
#include "ResourceManager.h"

dae::FpsComponent::FpsComponent()
	:m_Fps(0)
{
	m_pTextComp = new dae::TextComponent();
}
dae::FpsComponent::~FpsComponent()
{
	delete m_pTextComp;
}

void dae::FpsComponent::Update(float deltaTime)
{
	m_Fps = int(1 / deltaTime);
	m_pTextComp->SetText(std::to_string(m_Fps));
	m_pTextComp->Update(deltaTime);

}
void dae::FpsComponent::FixedUpdate(float)
{
}

void dae::FpsComponent::Render() const
{
	m_pTextComp->Render();
}

void dae::FpsComponent::SetPosition(float x, float y)
{
	m_pTextComp->SetPosition(x, y);
}

void dae::FpsComponent::SetFont(std::shared_ptr<Font> font)
{
	m_pTextComp->SetFont(font);
}

