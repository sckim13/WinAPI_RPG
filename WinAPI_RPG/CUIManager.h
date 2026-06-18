#pragma once

#include "CManager.h"

class CUIManager : public CManager
{
	SINGLETON(CUIManager);

public:
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

private:
	// All UI Pointers
};

