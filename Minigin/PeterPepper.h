#pragma once
#include "Component.h"

class PeterPepper : public Component
{
public:
	friend class GameObject;

	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);
	void Render() const;

	~PeterPepper();
	PeterPepper(const PeterPepper& other) = delete;
	PeterPepper(PeterPepper&& other) = delete;
	PeterPepper& operator=(const PeterPepper& other) = delete;
	PeterPepper& operator=(PeterPepper&& other) = delete;

private:
	PeterPepper();

};

