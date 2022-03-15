#include "MiniginPCH.h"
#include "InputManager.h"
#include "../3rdParty/imgui-1.87/backends/imgui_impl_sdl.h"
#include <Xinput.h>

class dae::InputManager::InputManagerImpl
{
public:
	void ProcessInput(dae::InputManager& inputManager);
	bool IsPressed(const dae::ControllerButton& button, const dae::ButtonActivateState& activateState, const dae::InputManager& inputManager) const;
	void CheckInput(dae::InputManager& inputManager);
	bool IsPressedThisFrame(int button) const;
private:
	XINPUT_STATE m_currentState{};
	XINPUT_STATE m_previousState{};
};

void dae::InputManager::InputManagerImpl::ProcessInput(dae::InputManager& inputManager)
{
	CopyMemory(&m_previousState, &m_currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_currentState);

	auto buttonChanges = m_currentState.Gamepad.wButtons ^ m_previousState.Gamepad.wButtons;
	inputManager.m_buttonPressedThisFrame = buttonChanges & m_currentState.Gamepad.wButtons;
	inputManager.m_buttonReleasedThisFrame = buttonChanges & (~m_currentState.Gamepad.wButtons);
}
bool dae::InputManager::InputManagerImpl::IsPressed(const dae::ControllerButton& button, const dae::ButtonActivateState& activateState, const dae::InputManager& inputManager) const
{

	switch (activateState)
	{
	case dae::ButtonActivateState::IsPressed:
		return inputManager.IsPressedThisFrame(int(button));
	case dae::ButtonActivateState::OnButtonDown:
		return inputManager.IsDownThisFrame(int(button));
	case dae::ButtonActivateState::OnButtonRelease:
		return inputManager.IsUpThisFrame(int(button));
	}
	return false;
}
void dae::InputManager::InputManagerImpl::CheckInput(dae::InputManager& inputManager)
{
	for (auto const& x : inputManager.m_consoleCommands)
	{
		if (IsPressed(x.first.first, x.first.second, inputManager))
		{
			x.second->Execute();
		}
	}
}
bool dae::InputManager::InputManagerImpl::IsPressedThisFrame(int button) const
{
	return m_currentState.Gamepad.wButtons & button;
}


////////

dae::InputManager::InputManager()
{
	m_pImpl = new InputManagerImpl();
}
dae::InputManager::~InputManager()
{
	delete m_pImpl;
}

bool dae::InputManager::ProcessInput()
{
	m_pImpl->ProcessInput(*this);



	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		ImGui_ImplSDL2_ProcessEvent(&e);
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN)
		{

		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{

		}
	}

	return true;
}

bool dae::InputManager::IsPressed(const ControllerButton& button, const ButtonActivateState& activateState) const
{
	return m_pImpl->IsPressed(button, activateState, *this);
}
void dae::InputManager::CheckInput()
{
	m_pImpl->CheckInput(*this);
}

bool dae::InputManager::IsDownThisFrame(int button) const
{
	return m_buttonPressedThisFrame & button;
}
bool dae::InputManager::IsUpThisFrame(int button) const
{
	return m_buttonReleasedThisFrame & button;
}
bool dae::InputManager::IsPressedThisFrame(int button) const
{
	return m_pImpl->IsPressedThisFrame(button);
}

void dae::InputManager::AddCommand(const ControllerButton& button, const ButtonActivateState& activateState, std::unique_ptr<Command> command)
{
	m_consoleCommands.insert(std::make_pair(std::make_pair(button, activateState), std::move(command)));
}
