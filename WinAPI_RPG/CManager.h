#pragma once

#include "CBase.h"

class CManager : public CBase
{
public:
	virtual void Initialize() PURE;
	virtual void PostInitialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Release() PURE;
	virtual void Render(HDC hDC) PURE;

protected:
	CManager();
	virtual ~CManager();

};

