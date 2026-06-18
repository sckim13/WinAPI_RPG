#pragma once

#include "pch.h"
#include "CObject.h"

// T is the event context to deliver
template<typename T>
class CEventHandle
{
public:
	void AddBinding(CObject* pObject, function<void(T)> F);
	void DeleteBinding(CObject* pObject);

	void Broadcast(T Context);

private:
	map<CObject*, function<void(T)>> m_mapEvent;
};

template<typename T>
void CEventHandle<T>::AddBinding(CObject* pObject, function<void(T)> F)
{
	m_mapEvent.insert({ pObject, F });
}

template<typename T>
void CEventHandle<T>::DeleteBinding(CObject* pObject)
{
	m_mapEvent.erase(pObject);
}

template<typename T>
void CEventHandle<T>::Broadcast(T Context)
{
	for (auto& pair : m_mapEvent)
	{
		pair.second(Context);
	}
}
