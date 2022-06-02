#include "MiniginPCH.h"
#include "Subject.h"
#include "observer.h"
//#include "Events.h"


dae::Subject::Subject()
	:m_head(nullptr)
{}
dae::Subject::~Subject()
{

}

void dae::Subject::addObserver(Observer* observer)
{
	observer->m_next = m_head;
	if(m_head != nullptr)
		m_head->m_previous = observer;
	observer->m_previous = nullptr;

	m_head = observer;
}
void dae::Subject::removeObserver(Observer* observer)
{
	observer->m_previous->m_next = observer->m_next;
	observer->m_next->m_previous= observer->m_previous;
}

void dae::Subject::Notify(const dae::GameObject& go, const Event& event)//todo event enum fix
{
	Observer* observer = m_head;
	while (observer != nullptr)
	{
		observer->onNotify(go, event);
		observer = observer->m_next;
	}
}
