#pragma once

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

	MAX,
};

struct tKeyInfo
{
	EKeyState eKeyState;
	bool bPressedOnLastUpdate;
	float fLastPressedTime; // for check double click
};

class CKeyManager
{
	SINGLETON(CKeyManager);

public:
	void Initialize();
	void Update();

	inline EKeyState GetKeyState(EKey eKey) { return m_vecKey[(int)eKey].eKeyState; }

private:
	vector<tKeyInfo> m_vecKey;
	float fDoubleClickThreshold = 0.2f;
};

