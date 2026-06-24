#pragma once

#include "CManager.h"

class CTimerManager : public CManager
{
	SINGLETON(CTimerManager);

public:
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;



private:

};

