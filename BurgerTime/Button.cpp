#include "BurgerTimePCH.h"
#include "Button.h"
#include "Renderer.h"


Button::Button(const glm::vec2& pos, const glm::vec2& size)
	:m_Pos(pos)
	, m_Size(size)
{

}
Button::~Button()
{

}

void Button::Render()
{
	SDL_Renderer* renderer = dae::Renderer::GetInstance().GetSDLRenderer();

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawLineF(renderer, m_Pos.x, m_Pos.y, m_Pos.x, m_Pos.y + m_Size.y);
	SDL_RenderDrawLineF(renderer, m_Pos.x, m_Pos.y + m_Size.y, m_Pos.x + m_Size.x, m_Pos.y + m_Size.y);
	SDL_RenderDrawLineF(renderer, m_Pos.x + m_Size.x, m_Pos.y + m_Size.y, m_Pos.x + m_Size.x, m_Pos.y);
	SDL_RenderDrawLineF(renderer, m_Pos.x + m_Size.x, m_Pos.y, m_Pos.x, m_Pos.y);

}
