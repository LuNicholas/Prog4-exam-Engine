#pragma once
#include <map>
#include "Command.h"
#include "Singleton.h"

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

	class InputManager final : public Singleton<InputManager>
	{
		class InputManagerImpl;
		InputManagerImpl* m_pImpl;

	public:
		InputManager();
		~InputManager();
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

		using ButtonInfo = std::pair<ControllerButton, ButtonActivateState>;
		using	ControllerCommandMap = std::map<ButtonInfo, std::unique_ptr<Command>>;
		ControllerCommandMap m_consoleCommands;
	};

}
