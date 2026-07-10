#pragma once

#define WINCX 1366
#define WINCY 768

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
	virtual ~Type();				\