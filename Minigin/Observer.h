#pragma once

enum class Event
{
	PlayerDied,
	ScoreIncrease
};


namespace dae
{
	class GameObject;

	class Observer
	{
		friend class Subject;

	public:
		Observer();
		virtual ~Observer();
		virtual void onNotify(const dae::GameObject& entity, Event event) = 0;
	private:
		std::shared_ptr<Observer> m_next;
		std::shared_ptr<Observer> m_previous;
	};

}