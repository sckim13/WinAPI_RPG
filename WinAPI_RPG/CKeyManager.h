#pragma once
#include "CManager.h"

template<typename T>
class CEventHandle;

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

	CEventHandle<TKeyEventCtx>* m_hOnKeyEventTriggered;
private:
	vector<tKeyInfo> m_vecKey;
	float fDoubleClickThreshold = 0.2f;

	map<EKey, EEventType> m_mapInputEvent;

};

