#include "MiniginPCH.h"
#include "Subject.h"
#include "observer.h"



Subject::Subject()
{}
Subject::~Subject()
{

}

void Subject::addObserver(Observer* observer)
{
	observer->m_next = m_head;
	m_head->m_previous = observer;
	observer->m_previous = nullptr;

	m_head = observer;
}
void Subject::removeObserver(Observer* observer)
{
	observer->m_previous->m_next = observer->m_next;
	observer->m_next->m_previous= observer->m_previous;
}

void Subject::Notify(const dae::GameObject& go, Event event)
{
	Observer* observer = m_head;
	while (observer != nullptr)
	{
		observer->onNotify(go, event);
		observer = observer->m_next;
	}
}
