#pragma once

#include "CObject.h"

class CCursor : public CObject
{
public:
	CCursor();
	virtual ~CCursor();

	void Initialize() override;
	void PostInitialize() override;
	void Update() override;
	void LateUpdate() override;
	void Release() override;
	void Render(HDC hDC) override;
};

