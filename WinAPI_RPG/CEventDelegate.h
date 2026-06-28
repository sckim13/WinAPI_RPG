#pragma once

using namespace std;
#include <functional>
#include <map>

// T is the event context to deliver
template<typename T>
class CEventDelegate
{
public:
	void AddBinding(INT64 ID, function<void(const T&)> F);
	void DeleteBinding(INT64 ID);

	void Broadcast(T Ctx);

private:
	map<INT64, function<void(T)>> m_mapEvent;
};

template<typename T>
void CEventDelegate<T>::AddBinding(INT64 ID, function<void(const T&)> F)
{
	m_mapEvent.insert({ ID, F });
}

template<typename T>
void CEventDelegate<T>::DeleteBinding(INT64 ID)
{
	m_mapEvent.erase(ID);
}

template<typename T>
void CEventDelegate<T>::Broadcast(T Ctx)
{
	for (auto& pair : m_mapEvent)
	{
		pair.second(Ctx);
	}
}

template<>
class CEventDelegate<void>
{
public:
	void AddBinding(INT64 ID, function<void()> F);
	void DeleteBinding(INT64 ID);

	void Broadcast();

private:
	map<INT64, function<void()>> m_mapEvent;
};
