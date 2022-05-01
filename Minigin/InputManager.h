#pragma once
#include "PcController.h"
#include <vector>
#include "Singleton.h"

namespace dae
{

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();
		bool ProcessInput();
		bool IsPressed(const ControllerButton& button, const ButtonActivateState& activateState, int controllerNr) const;
		void AddCommand(const ControllerButton& button, const ButtonActivateState& activateState, std::unique_ptr<Command> command, int controllerNr);
		void CheckInput();

		bool IsDownThisFrame(int button, int controllerNr) const;
		bool IsUpThisFrame(int button, int controllerNr) const;
		bool IsPressedThisFrame(int button, int controllerNr) const;

	private:
		std::vector<PcController*> m_pControllers;

		using ButtonInfo = std::pair<ControllerButton, ButtonActivateState>;
		using	ControllerCommandMap = std::map<ButtonInfo, std::unique_ptr<Command>>;
		ControllerCommandMap m_consoleCommands;
	};

}

