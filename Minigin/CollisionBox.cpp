#include "MiniginPCH.h"
#include "CollisionBox.h"
#include "Renderer.h"

std::vector<dae::CollisionBox*> dae::CollisionBox::m_CollisionBoxes{};

dae::CollisionBox::CollisionBox()
	:m_Width(0)
	, m_Height(0)
{
	m_CollisionBoxes.push_back(this);
}
dae::CollisionBox::~CollisionBox()
{
}

void dae::CollisionBox::Update(float deltaTime)
{
}
void dae::CollisionBox::FixedUpdate(float deltaTime)
{
}
void dae::CollisionBox::Render() const
{
	DrawBox();
}

void dae::CollisionBox::SetBox(int width, int height)
{
	m_Width = width;
	m_Height = height;
}
glm::vec4 dae::CollisionBox::GetBox()
{
	glm::vec3 currentPos = m_Transform.GetPosition();

	return glm::vec4(currentPos.x, currentPos.y, m_Width, m_Height);
}

void dae::CollisionBox::SetTag(const std::string& tag)
{
	m_Tag = tag;
}
std::string dae::CollisionBox::GetTag()
{
	return m_Tag;
}

void dae::CollisionBox::DrawBox() const
{
	glm::vec3 transform = m_Transform.GetPosition();

	SDL_Renderer* renderer = Renderer::GetInstance().GetSDLRenderer();

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawLineF(renderer, transform.x, transform.y, transform.x, transform.y + m_Height);
	SDL_RenderDrawLineF(renderer, transform.x, transform.y + m_Height, transform.x + m_Width, transform.y + m_Height);
	SDL_RenderDrawLineF(renderer, transform.x + m_Width, transform.y + m_Height, transform.x + m_Width, transform.y);
	SDL_RenderDrawLineF(renderer, transform.x + m_Width, transform.y, transform.x, transform.y);
}

std::vector<dae::CollisionBox*> dae::CollisionBox::GetCollidingWith()
{
	std::vector<dae::CollisionBox*> colliding;

	for (dae::CollisionBox* collider : m_CollisionBoxes)
	{
		if (this != collider)
		{
			if (IsOverlappingWith(collider))
			{
				colliding.push_back(collider);
			}
		}
	}

	return colliding;
}
bool dae::CollisionBox::IsOverlappingWith(dae::CollisionBox* collider)
{
	glm::vec3 thisPos = m_Transform.GetPosition();
	glm::vec3 otherPos = collider->m_Transform.GetPosition();

	if (thisPos.x >= otherPos.x + collider->m_Width || thisPos.x + m_Width <= otherPos.x)
		return false;


	if (thisPos.y >= otherPos.y + collider->m_Height || thisPos.y + m_Height <= otherPos.y)
		return false;


	return true;
}

bool  dae::CollisionBox::IsPointInCollider(const glm::vec2& point)
{
	glm::vec3 thisPos = m_Transform.GetPosition();

	if (point.x <= thisPos.x || point.x >= thisPos.x + m_Width)
		return false;


	if (point.y <= thisPos.y || point.y >= thisPos.y + m_Height)
		return false;


	return true;
}

glm::vec2 dae::CollisionBox::GetSize()
{
	return glm::vec2(m_Width, m_Height);
}