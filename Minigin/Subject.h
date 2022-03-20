#pragma once


enum class Event;

namespace dae
{
	class GameObject;
	class Observer;

	class Subject
	{
	public:
		Subject();
		~Subject();

		void addObserver(Observer* observer);
		void removeObserver(Observer* observer);

	protected:
		void Notify(const GameObject& go, Event event);

	private:
		Observer* m_head;
	};
}
