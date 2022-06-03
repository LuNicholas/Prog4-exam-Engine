#pragma once
#include "Command.h"
#include "Subject.h"

namespace dae
{
	class GameObject;
}

class PepperCommand : public Command
{

public:
	explicit PepperCommand(dae::GameObject* actor);
	void Execute() override;
private:
	dae::GameObject* m_actor;
};

class BunDropped : public Command, public dae::Subject
{

public:
	explicit BunDropped(dae::GameObject* actor);
	void Execute() override;
private:
	dae::GameObject* m_actor;
};

class MoveLeft : public Command
{

public:
	explicit MoveLeft(std::shared_ptr<dae::GameObject> actor);
	void Execute() override;
private:
	std::shared_ptr<dae::GameObject> m_actor;
};

class MoveRight : public Command
{

public:
	explicit MoveRight(std::shared_ptr<dae::GameObject> actor);
	void Execute() override;
private:
	std::shared_ptr<dae::GameObject> m_actor;
};

class MoveUp : public Command
{

public:
	explicit MoveUp(std::shared_ptr<dae::GameObject> actor);
	void Execute() override;
private:
	std::shared_ptr<dae::GameObject> m_actor;
};

class MoveDown : public Command
{

public:
	explicit MoveDown(std::shared_ptr<dae::GameObject> actor);
	void Execute() override;
private:
	std::shared_ptr<dae::GameObject> m_actor;
};

class IdleForward : public Command
{

public:
	explicit IdleForward(std::shared_ptr<dae::GameObject> actor);
	void Execute() override;
private:
	std::shared_ptr<dae::GameObject> m_actor;
};
class IdleUp : public Command
{

public:
	explicit IdleUp(std::shared_ptr<dae::GameObject> actor);
	void Execute() override;
private:
	std::shared_ptr<dae::GameObject> m_actor;
};


class PlaySound : public Command
{

public:
	explicit PlaySound(int soundId);
	void Execute() override;
private:
	int m_SoundId;
};

class PeterPepper;
class ButtonManager;
class NextScene : public Command
{

public:
	explicit NextScene(ButtonManager* buttonManager, PeterPepper* player1, PeterPepper* player2);
	void Execute() override;

private:
	ButtonManager* m_pButtonManager;
	PeterPepper* m_pPlayer1;
	PeterPepper* m_pPlayer2;
};


class NextButton : public Command
{

public:
	explicit NextButton(ButtonManager* buttonManager);
	void Execute() override;
private:
	ButtonManager* m_pButtonManager;
};

class PreviousButton : public Command
{

public:
	explicit PreviousButton(ButtonManager* buttonManager);
	void Execute() override;
private:
	ButtonManager* m_pButtonManager;
};