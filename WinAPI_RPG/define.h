#pragma once

#define SINGLETON(Type)				\
public:								\
	static Type* GetInstance()		\
	{								\
		static Type g_Inst;			\
		return &g_Inst;				\
	}								\
									\
private:							\
	Type();							\
	~Type();						\

