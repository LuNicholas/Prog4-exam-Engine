#pragma once


class Component abstract
{
public:

	virtual ~Component() = default;

	virtual void Update(float deltaTime) = 0;
	virtual void FixedUpdate(float deltaTime) = 0;
	virtual void Render() const = 0;

protected:
	Component() = default;
};

