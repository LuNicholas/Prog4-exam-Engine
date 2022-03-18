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

		void addObserver(dae::Observer* observer);
		void removeObserver(dae::Observer* observer);

	protected:
		void Notify(const dae::GameObject& go, Event event);

	private:
		dae::Observer* m_head;
	};
}
