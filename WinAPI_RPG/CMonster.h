#pragma once

#include "CCharacter.h"

struct TCollisionCtx;

class CMonster : public CCharacter
{
public:
	CMonster();
	virtual ~CMonster();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	void OnCollisionEntered(TCollisionCtx Ctx);

private:
};

