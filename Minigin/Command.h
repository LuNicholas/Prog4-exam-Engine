#pragma once
#include <iostream>
#include "Subject.h"

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};

