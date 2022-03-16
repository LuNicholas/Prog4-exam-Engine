#pragma once

namespace dae
{
	class GameObject;
}

enum class Event
{
	PlayerDied
};


class Observer
{
	friend class Subject;

public:
	Observer();
	~Observer();
	virtual void onNotify(const dae::GameObject& entity, Event event) = 0;

private:
	Observer* m_next;
	Observer* m_previous;
};

