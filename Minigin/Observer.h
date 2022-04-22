#pragma once

enum class Event
{
	PlayerHit,
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
		Observer* m_next;
		Observer* m_previous;
	};

}