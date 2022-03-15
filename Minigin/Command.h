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
