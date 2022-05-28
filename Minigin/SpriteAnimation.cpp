#include "MiniginPCH.h"
#include "SpriteAnimation.h"
#include "Texture2DComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Transform.h"



dae::SpriteAnimation::SpriteAnimation(const std::string& spriteSheet, int width, int height, int col, int row, float frameTime)
	:m_SizeTexture(width, height)
	,m_Col(col)
	,m_Row(row)
	, m_FrameTime(frameTime)
	, m_Size(width / m_Col, height / row)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(spriteSheet);
}
dae::SpriteAnimation::~SpriteAnimation()
{

}

void dae::SpriteAnimation::Update(float deltaTime)
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
void dae::SpriteAnimation::FixedUpdate(float)
{
}
void dae::SpriteAnimation::Render() const
{
	Renderer::GetInstance().RenderTexture(*m_Texture, GetDestRect(), GetsrcRect());
}


//void dae::SpriteAnimation::SetRowCol(int rows, int cols)
//{
//	m_Row = rows;
//	m_Col = cols;
//}
//void dae::SpriteAnimation::SetTextureSize(int w, int h)
//{
//	m_SizeTexture.x = float(w);
//	m_SizeTexture.y = float(h);
//
//	
//	m_Size.x = m_SizeTexture.x / m_Col;
//	m_Size.y = m_SizeTexture.y / m_Row;
//}
//void dae::SpriteAnimation::SetTexture(const std::string& filename)
//{
//	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
//}
//void dae::SpriteAnimation::SetFrameTime(float time)
//{
//	m_FrameTime = time;
//}

glm::vec4 dae::SpriteAnimation::GetDestRect() const
{
	return glm::vec4( m_Transform.GetPosition().x, m_Transform.GetPosition().y, m_Size.x, m_Size.y);
}
glm::vec4 dae::SpriteAnimation::GetsrcRect() const
{
	int row = m_CurrentSprite / m_Col;
	int col = m_CurrentSprite % m_Col;

	return glm::vec4{col * m_Size.x, row * m_Size.y, m_Size.x, m_Size.y };
}

void dae::SpriteAnimation::SetTransform(const Transform& transform)
{
	m_Transform = transform;
}