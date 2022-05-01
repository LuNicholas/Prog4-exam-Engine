#include "MiniginPCH.h"
#include "InputManager.h"
#include "../3rdParty/imgui-1.87/backends/imgui_impl_sdl.h"
#include <Xinput.h>


////////

dae::InputManager::InputManager()
{
	for (int i = 0; i < XUSER_MAX_COUNT; i++)
	{
		m_pControllers.push_back(new PcController(i));
	}
}
dae::InputManager::~InputManager()
{
	for (PcController* controller : m_pControllers)
	{
		delete controller;
	}
}

bool dae::InputManager::ProcessInput()
{
	for (PcController* controller : m_pControllers)
	{
		controller->ProcessInput();
	}


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

void dae::InputManager::CheckInput()
{
	for (PcController* controller : m_pControllers)
	{
		controller->CheckInput();
	}
}

bool dae::InputManager::IsPressed(const ControllerButton& button, const ButtonActivateState& activateState, int controllerNr) const
{
	return m_pControllers.at(controllerNr)->IsPressed(button, activateState);
}
bool dae::InputManager::IsDownThisFrame(int button, int controllerNr) const
{
	return m_pControllers.at(controllerNr)->IsDownThisFrame(button);
}
bool dae::InputManager::IsUpThisFrame(int button, int controllerNr) const
{
	return m_pControllers.at(controllerNr)->IsUpThisFrame(button);
}
bool dae::InputManager::IsPressedThisFrame(int button, int controllerNr) const
{
	return m_pControllers.at(controllerNr)->IsPressedThisFrame(button);
}

void dae::InputManager::AddCommand(const ControllerButton& button, const ButtonActivateState& activateState, std::unique_ptr<Command> command, int controllerNr)
{
	if (controllerNr > XUSER_MAX_COUNT - 1)
		return;

	m_pControllers.at(controllerNr)->AddCommand(button, activateState, std::move(command));
}