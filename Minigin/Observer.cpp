#include "MiniginPCH.h"
#include "Observer.h"


Observer::Observer()
	:m_next(nullptr)
	, m_previous(nullptr)
{

}

Observer::~Observer()
{
	m_next->m_previous = m_previous;
	m_previous->m_next = m_next;
}