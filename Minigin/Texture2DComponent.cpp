#include "MiniginPCH.h"
#include "Texture2DComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::Texture2DComponent::Texture2DComponent()
	:m_Visible(true)
{
	
}


void dae::Texture2DComponent::Update(float)
{
	if (!m_Visible)
		return;
}
void dae::Texture2DComponent::FixedUpdate(float)
{
	if (!m_Visible)
		return;
}
void dae::Texture2DComponent::Render() const
{
	if (!m_Visible)
		return;

	const auto& pos = m_Transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

void dae::Texture2DComponent::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}
void dae::Texture2DComponent::SetTexture(std::string filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::Texture2DComponent::SetVisibility(bool visibility)
{
	m_Visible = visibility;
}