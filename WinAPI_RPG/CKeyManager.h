#pragma once
#include "CManager.h"

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
	// Alphabet Layer
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H, 
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	COMMA,
	DOT,
	SLASH,
	COLON,
	QUOTE,
	LBRACKET,
	RBRACKET,
	
	// Upper Number Layer
	TILDE,
	N0,
	N1,
	N2,
	N3,
	N4,
	N5,
	N6,
	N7,
	N8,
	N9,
	MINUS,
	PLUS,
	
	// Function Key Layer
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,

	// Arrow Key
	LEFT,
	RIGHT,
	UP,
	DOWN,

	// Peripheral
	ESCAPE,
	TAB,
	CAPSLOCK,
	SHIFT,
	CTRL,
	ALT,
	SPACE,
	ENTER,
	RSLASH,
	BACKSPACE,

	// Arrow Upper Layer
	PRINTSCREEN,
	SCROLLLOCK,
	PAUSELOCK,
	INSERT,
	HOME,
	PAGEUP,
	DELETEKEY,
	END,
	PAGEDOWN,

	// Mouse
	L_CLICK,
	R_CLICK,
	M_CLICK,

	MAX,
};

struct tKeyInfo
{
	EKeyState eKeyState;
	bool bPressedOnLastUpdate;
	float fLastPressedTime; // for check double click
};

class CKeyManager : public CManager
{
	SINGLETON(CKeyManager);

public:
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	inline EKeyState GetKeyState(EKey eKey) { return m_vecKey[(int)eKey].eKeyState; }

private:
	vector<tKeyInfo> m_vecKey;
	float fDoubleClickThreshold = 0.2f;
};

