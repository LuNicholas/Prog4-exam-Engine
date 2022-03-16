#pragma once

namespace dae
{
	class GameObject;
}
class Observer;
enum class Event;

class Subject
{
public:
	Subject();
	~Subject();

	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);

protected:
	void Notify(const dae::GameObject& go, Event event);

private:
	Observer* m_head;
};

