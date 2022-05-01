#pragma once
#include <windows.h>
#include <map>
#include <memory>
#include "Command.h"

namespace dae
{
	enum class ControllerButton
	{
		DpadUp = 0x0001,
		DpadDown = 0x0002,
		DpadLeft = 0x0004,
		DpadRight = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		LeftThumb = 0x0040,
		RightThumb = 0x0080,
		LeftShoulder = 0x0100,
		RightShoulder = 0x0200,
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
	};
	enum class ButtonActivateState
	{
		OnButtonDown,
		IsPressed,
		OnButtonRelease,
	};

	class PcController final
	{
		class ControllerImpl;
		ControllerImpl* m_pImpl;

	public:
		PcController(int controllerNr);
		~PcController();
		bool ProcessInput();
		bool IsPressed(const ControllerButton& button, const ButtonActivateState& activateState) const;
		void AddCommand(const ControllerButton& button, const ButtonActivateState& activateState, std::unique_ptr<Command> command);
		void CheckInput();

		bool IsDownThisFrame(int button) const;
		bool IsUpThisFrame(int button) const;
		bool IsPressedThisFrame(int button) const;

	private:

		int m_buttonPressedThisFrame{};
		int m_buttonReleasedThisFrame{};

		const int m_controllerNr;
		bool m_IsConnected = false;

		using ButtonInfo = std::pair<ControllerButton, ButtonActivateState>;
		using	ControllerCommandMap = std::map<ButtonInfo, std::unique_ptr<Command>>;
		ControllerCommandMap m_consoleCommands;
	};

}


