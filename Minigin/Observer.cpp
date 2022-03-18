#include "MiniginPCH.h"
#include "Observer.h"


dae::Observer::Observer()
	:m_next(nullptr)
	, m_previous(nullptr)
{

}

dae::Observer::~Observer()
{
	if (m_next != nullptr)
		m_next->m_previous = m_previous;

	if (m_previous != nullptr)
		m_previous->m_next = m_next;
}