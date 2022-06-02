#include "BurgerTimePCH.h"
#include "ButtonManager.h"
#include "Button.h"


ButtonManager::ButtonManager()
	:m_CurrentButton(0)
{
}
ButtonManager::~ButtonManager()
{
}

void ButtonManager::Update(float deltaTime)
{
}
void ButtonManager::FixedUpdate(float deltaTime)
{
}
void ButtonManager::Render() const
{
	if (m_Buttons.size() > 0)
	{
		m_Buttons[m_CurrentButton]->Render();
	}
}

void ButtonManager::AddButton(glm::vec2 pos, const glm::vec2& size)
{
	m_Buttons.push_back(new Button(pos, size));
}
void ButtonManager::NextButton()
{
	m_CurrentButton++;
	if (m_CurrentButton >= m_Buttons.size())
		m_CurrentButton = 0;
}
void ButtonManager::PreviousButton()
{
	m_CurrentButton--;
	if (m_CurrentButton < 0)
		m_CurrentButton = m_Buttons.size()-1;
}