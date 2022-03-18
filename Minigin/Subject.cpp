#include "MiniginPCH.h"
#include "Subject.h"
#include "observer.h"



dae::Subject::Subject()
	:m_head(nullptr)
{}
dae::Subject::~Subject()
{
	//leak is probably here
	dae::Observer* temp;

	while (m_head != nullptr) {
		temp = m_head;
		m_head = m_head->m_next;
		delete temp;
	}
}

void dae::Subject::addObserver(dae::Observer* observer)
{
	observer->m_next = m_head;
	if(m_head != nullptr)
		m_head->m_previous = observer;
	observer->m_previous = nullptr;

	m_head = observer;
}
void dae::Subject::removeObserver(dae::Observer* observer)
{
	observer->m_previous->m_next = observer->m_next;
	observer->m_next->m_previous= observer->m_previous;
}

void dae::Subject::Notify(const dae::GameObject& go, Event event)
{
	dae::Observer* observer = m_head;
	while (observer != nullptr)
	{
		observer->onNotify(go, event);
		observer = observer->m_next;
	}
}
