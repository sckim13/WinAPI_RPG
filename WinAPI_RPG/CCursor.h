#pragma once

#include "CObject.h"

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
	POINT m_ptCursorPos;

public:
};

