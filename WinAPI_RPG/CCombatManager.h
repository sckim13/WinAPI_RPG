#pragma once

#include "CManager.h"

class CCharacter;

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

	CEventDelegate<TCombatCtx> m_OnCombatTriggered;

	void RequestDamage(CCharacter* pCharacter, const vector<long long>& vecDamage);

private:
	// random value picking
	mt19937 m_gen;



};

