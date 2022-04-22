#pragma once
#include <iostream>
#include "Subject.h"

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};

class JumpCommand : public Command
{
public:
	void Execute() override { std::cout << "Jump" << std::endl; }
};

class FireCommand : public Command
{
public:
	void Execute() override { std::cout << "Fire" << std::endl; }
};

class DuckCommand : public Command
{
public:
	void Execute() override { std::cout << "Duck" << std::endl; }
};

class FartCommand : public Command
{
public:
	void Execute() override { std::cout << "Fart" << std::endl; }
};

namespace dae
{
	class GameObject;
}

class HitCommand : public Command
{

public:
	explicit HitCommand(dae::GameObject* actor);
	void Execute() override;
private:
	dae::GameObject* m_actor;
};

class AddScoreCommand : public Command, public dae::Subject
{

public:
	explicit AddScoreCommand(dae::GameObject* actor);
	void Execute() override;
private:
	dae::GameObject* m_actor;
};

class MoveLeft : public Command, public dae::Subject
{

public:
	explicit MoveLeft(std::shared_ptr<dae::GameObject> actor);
	void Execute() override;
private:
	std::shared_ptr<dae::GameObject> m_actor;
};

class MoveRight : public Command, public dae::Subject
{

public:
	explicit MoveRight(std::shared_ptr<dae::GameObject> actor);
	void Execute() override;
private:
	std::shared_ptr<dae::GameObject> m_actor;
};
