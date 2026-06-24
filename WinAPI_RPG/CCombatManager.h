#pragma once

#include "CManager.h"

class CCombatManager : public CManager
{
	SINGLETON(CCombatManager);

public:
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	CEventDelegate<TCombatCtx> m_hOnCombatTriggered;

};

