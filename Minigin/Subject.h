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

		void addObserver(std::shared_ptr<Observer> observer);
		void removeObserver(std::shared_ptr<Observer> observer);

	protected:
		void Notify(const GameObject& go, Event event);

	private:
		std::shared_ptr<Observer> m_head;
	};
}
