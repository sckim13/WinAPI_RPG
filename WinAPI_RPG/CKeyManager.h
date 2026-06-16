#pragma once
#include "CManagerBase.h"

enum class EKeyState
{
	NONE,
	PRESSED,
	DOUBLE_PRESSED,
	HOLD,
	RELEASED,
};

enum class EKey
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	ESCAPE,

	MAX,
};

struct tKeyInfo
{
	EKeyState eKeyState;
	bool bPressedOnLastUpdate;
	float fLastPressedTime; // for check double click
};

class CKeyManager : public CManagerBase
{
	SINGLETON(CKeyManager);

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	inline EKeyState GetKeyState(EKey eKey) { return m_vecKey[(int)eKey].eKeyState; }

private:
	vector<tKeyInfo> m_vecKey;
	float fDoubleClickThreshold = 0.2f;
};

