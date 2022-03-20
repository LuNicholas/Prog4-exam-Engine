#pragma once
#include <iostream>

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

class AddScoreCommand : public Command
{

public:
	explicit AddScoreCommand(dae::GameObject* actor);
	void Execute() override;
private:
	dae::GameObject* m_actor;
};
