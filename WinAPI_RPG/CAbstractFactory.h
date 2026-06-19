#pragma once

template<typename TBase, typename TDerived>
class CAbstractFactory
{
public:
	static TBase* Create()
	{
		TBase* p = new TDerived;
		p->Initialize();
		return p;
	}
};

