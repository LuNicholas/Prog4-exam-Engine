#include "MiniginPCH.h"
#include "AnimationComponent.h"
#include "Texture2DComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"



dae::SpriteAnimationComponent::SpriteAnimationComponent()
{

}
dae::SpriteAnimationComponent::~SpriteAnimationComponent()
{

}

void dae::SpriteAnimationComponent::Update(float deltaTime)
{
	m_CurrentFrameTime += deltaTime;
	if (m_CurrentFrameTime >= m_FrameTime)
	{
		m_CurrentSprite++;
		if (m_CurrentSprite >= m_Row * m_Col)
		{
			m_CurrentSprite = 0;
		}
		m_CurrentFrameTime = 0;
	}
}
void dae::SpriteAnimationComponent::FixedUpdate(float)
{
}
void dae::SpriteAnimationComponent::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_Texture, GetDestRect(), GetsrcRect());
}


void dae::SpriteAnimationComponent::SetRowCol(int rows, int cols)
{
	m_Row = rows;
	m_Col = cols;
}
void dae::SpriteAnimationComponent::SetTextureSize(int w, int h)
{
	m_SizeTexture.x = float(w);
	m_SizeTexture.y = float(h);

	
	m_Size.x = m_SizeTexture.x / m_Col;
	m_Size.y = m_SizeTexture.y / m_Row;
}
void dae::SpriteAnimationComponent::SetTexture(std::string filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}
void dae::SpriteAnimationComponent::SetFrameTime(float time)
{
	m_FrameTime = time;
}

glm::vec4 dae::SpriteAnimationComponent::GetDestRect() const
{
	return glm::vec4( m_Transform.GetPosition().x, m_Transform.GetPosition().y, m_Size.x, m_Size.y);
}
glm::vec4 dae::SpriteAnimationComponent::GetsrcRect() const
{
	int row = m_CurrentSprite / m_Col;
	int col = m_CurrentSprite % m_Col;

	return glm::vec4{col * m_Size.x, row * m_Size.y, m_Size.x, m_Size.y };
}