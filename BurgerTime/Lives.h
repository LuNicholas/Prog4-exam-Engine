#pragma once
#include <Component.h>
#include "Subject.h"

class Lives final: public dae::Component ,public dae::Subject
{
public:

	friend class dae::GameObject;

	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);
	void Render() const;

	void Init(int lives);

	~Lives();
	Lives(const Lives& other) = delete;
	Lives(Lives&& other) = delete;
	Lives& operator=(const Lives& other) = delete;
	Lives& operator=(Lives&& other) = delete;


private:
	Lives();

	int m_Lives;
};

