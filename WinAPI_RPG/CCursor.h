#pragma once

#include "CObject.h"

class CAnimator;

class CCursor : public CObject
{
public:
	CCursor();
	virtual ~CCursor();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

private:
	IPoint m_ptCursorPos;
	ECursorState m_eCursorState;
	CAnimator* m_pAnimator;

public:
	inline void SetCursorState(ECursorState eState) { m_eCursorState = eState; }
};

