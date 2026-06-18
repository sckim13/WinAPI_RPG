#pragma once

#include "CObject.h"

class CUI
{
public:
	CUI();
	virtual ~CUI();

private:
	virtual void Initialize() PURE;
	virtual void PostInitialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Release() PURE;
	virtual void Render(HDC hDC) PURE;

};

