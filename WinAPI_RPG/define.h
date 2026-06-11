#pragma once

#define SINGLETON(Type)				\
public:								\
	static Type* GetInstance()		\
	{								\
		if (!g_pInst)				\
		{							\
			g_pInst = new Type;		\
		}							\
		return g_pInst;				\
	}								\
									\
	static void Release()			\
	{								\
		if (g_pInst)				\
		{							\
			delete g_pInst;			\
			g_pInst = nullptr;		\
		}							\
	}								\
									\
private:							\
	Type();							\
	~Type();						\
	static Type* g_pInst;			\

