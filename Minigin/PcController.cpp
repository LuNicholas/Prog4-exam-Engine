#include "MiniginPCH.h"
#include "PcController.h"
#include "InputManager.h"
#include <Xinput.h>


class dae::PcController::ControllerImpl
{
public:
	ControllerImpl();

	void ProcessInput(dae::PcController& controller);
	bool IsPressed(const dae::ControllerButton& button, const dae::ButtonActivateState& activateState, const dae::PcController& controller) const;
	void CheckInput(dae::PcController& controller);
	bool IsPressedThisFrame(int button) const;
private:
	XINPUT_STATE m_currentState{};
	XINPUT_STATE m_previousState{};

	
};

dae::PcController::ControllerImpl::ControllerImpl()
{
}
void dae::PcController::ControllerImpl::ProcessInput(dae::PcController& controller)
{
	CopyMemory(&m_previousState, &m_currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
	const DWORD dwResult = XInputGetState(controller.m_controllerNr, &m_currentState);
	controller.m_IsConnected = (dwResult == ERROR_SUCCESS);

	auto buttonChanges = m_currentState.Gamepad.wButtons ^ m_previousState.Gamepad.wButtons;
	controller.m_buttonPressedThisFrame = buttonChanges & m_currentState.Gamepad.wButtons;
	controller.m_buttonReleasedThisFrame = buttonChanges & (~m_currentState.Gamepad.wButtons);
}
bool dae::PcController::ControllerImpl::IsPressed(const dae::ControllerButton& button, const dae::ButtonActivateState& activateState, const dae::PcController& controller) const
{

	switch (activateState)
	{
	case dae::ButtonActivateState::IsPressed:
		return controller.IsPressedThisFrame(int(button));
	case dae::ButtonActivateState::OnButtonDown:
		return controller.IsDownThisFrame(int(button));
	case dae::ButtonActivateState::OnButtonRelease:
		return controller.IsUpThisFrame(int(button));
	}
	return false;
}
void dae::PcController::ControllerImpl::CheckInput(dae::PcController& controller)
{
	for (auto const& x : controller.m_consoleCommands)
	{
		if (IsPressed(x.first.first, x.first.second, controller))
		{
			x.second->Execute();
		}
	}
}
bool dae::PcController::ControllerImpl::IsPressedThisFrame(int button) const
{

	return m_currentState.Gamepad.wButtons & button;

}


////////

dae::PcController::PcController(int controllerNr)
	:m_controllerNr(controllerNr)
{
	m_pImpl = new ControllerImpl();
}
dae::PcController::~PcController()
{
	delete m_pImpl;
}

bool dae::PcController::ProcessInput()
{
	m_pImpl->ProcessInput(*this);
	return true;
}

bool dae::PcController::IsPressed(const ControllerButton& button, const ButtonActivateState& activateState) const
{
	if (!m_IsConnected)
		return false;

	return m_pImpl->IsPressed(button, activateState, *this);
}
void dae::PcController::CheckInput()
{
	if (!m_IsConnected)
		return;

	m_pImpl->CheckInput(*this);
}

bool dae::PcController::IsDownThisFrame(int button) const
{
	if (!m_IsConnected)
		return false;

	return m_buttonPressedThisFrame & button;
}
bool dae::PcController::IsUpThisFrame(int button) const
{
	if (!m_IsConnected)
		return false;

	return m_buttonReleasedThisFrame & button;
}
bool dae::PcController::IsPressedThisFrame(int button) const
{
	if (!m_IsConnected)
		return false;

	return m_pImpl->IsPressedThisFrame(button);
}

void dae::PcController::AddCommand(const ControllerButton& button, const ButtonActivateState& activateState, std::unique_ptr<Command> command)
{
	m_consoleCommands.insert(std::make_pair(std::make_pair(button, activateState), std::move(command)));
}
