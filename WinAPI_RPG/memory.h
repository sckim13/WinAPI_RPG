#pragma once

#include <type_traits>

template<typename T>
void Safe_Delete(T& p)
{
	static_assert(sizeof(std::remove_pointer_t<T>) > 0,
		"[Safe_Delete] Incomplete Type - Destructor may not be called");
	if (p)
	{
		delete p;
		p = nullptr;
	}
}