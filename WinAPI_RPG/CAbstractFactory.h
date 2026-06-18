#pragma once

template<typename T>
class CAbstractFactory
{
	static T* Create()
	{
		T* p = new T;
		return p;
	}
};

