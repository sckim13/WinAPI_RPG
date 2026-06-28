#include "pch.h"
#include "CEventDelegate.h"


void CEventDelegate<void>::AddBinding(INT64 ID, function<void()> F)
{
	m_mapEvent.insert({ ID, F });
}

void CEventDelegate<void>::DeleteBinding(INT64 ID)
{
	m_mapEvent.erase(ID);
}

void CEventDelegate<void>::Broadcast()
{
	for (auto& pair : m_mapEvent)
	{
		pair.second();
	}
}