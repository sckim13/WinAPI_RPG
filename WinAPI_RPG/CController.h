#pragma once

#include "CComponent.h"

class CCharacter;

class CController : public CComponent
{
public:
	CController();
	virtual ~CController();

	void Initialize() override;
	void PostInitialize() override;
	void Update() override;
	void LateUpdate() override;
	void Release() override;
	void Render(HDC hDC) override;

private:
	CCharacter* m_pPossess;

public:
	inline void SetCharacter(CCharacter* pChar) { m_pPossess = pChar; }
	inline CCharacter* GetCharacter() { return m_pPossess; }
};

