#pragma once

class Button
{
public:
	Button(const glm::vec2& pos, const glm::vec2& size);
	~Button();

	void Render();

private:

	glm::vec2 m_Pos;
	glm::vec2 m_Size;

};

