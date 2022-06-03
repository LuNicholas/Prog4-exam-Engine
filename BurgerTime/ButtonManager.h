#pragma once
#include <Component.h>

class Button;

class ButtonManager final : public dae::Component
{

	friend class dae::GameObject;
public:
	~ButtonManager();

	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);
	void Render() const;

	void AddButton(glm::vec2 pos, const glm::vec2& size);
	void NextButton();
	void PreviousButton();
	int GetCurrentButton() const;

	ButtonManager(const ButtonManager& other) = delete;
	ButtonManager(ButtonManager&& other) = delete;
	ButtonManager& operator=(const ButtonManager& other) = delete;
	ButtonManager& operator=(ButtonManager&& other) = delete;

private:
	ButtonManager();

	std::vector<Button*> m_Buttons;

	int m_CurrentButton;
};

