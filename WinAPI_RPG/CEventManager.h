#pragma once

#include "CManager.h"

class CEventManager : public CManager
{
	SINGLETON(CEventManager);

public:
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	void AddEvent();
	void RemoveEvent();

private:
	/* event queue container */

};

