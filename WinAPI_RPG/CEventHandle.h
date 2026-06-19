#pragma once

using namespace std;
#include <functional>
#include <map>

class CBase;

// T is the event context to deliver
template<typename T>
class CEventHandle
{
public:
	void AddBinding(CBase* pBase, function<void(T)> F);
	void DeleteBinding(CBase* pBase);

	void Broadcast(T Ctx);

private:
	map<CBase*, function<void(T)>> m_mapEvent;
};

template<typename T>
void CEventHandle<T>::AddBinding(CBase* pBase, function<void(T)> F)
{
	m_mapEvent.insert({ pBase, F });
}

template<typename T>
void CEventHandle<T>::DeleteBinding(CBase* pBase)
{
	m_mapEvent.erase(pBase);
}

template<typename T>
void CEventHandle<T>::Broadcast(T Ctx)
{
	for (auto& pair : m_mapEvent)
	{
		pair.second(Ctx);
	}
}
