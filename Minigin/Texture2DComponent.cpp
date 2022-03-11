#include "MiniginPCH.h"
#include "Texture2DComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::Texture2DComponent::Texture2DComponent()
{
	
}


void dae::Texture2DComponent::Update(float)
{

}
void dae::Texture2DComponent::FixedUpdate(float)
{

}
void dae::Texture2DComponent::Render() const
{
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