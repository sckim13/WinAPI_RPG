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

	virtual void OnCollisionBegin(const TCollisionCtx& Ctx) override;
	virtual void OnCollision(const TCollisionCtx& Ctx) override;
	virtual void OnCollisionEnd(const TCollisionCtx& Ctx) override;

	virtual void OnHit(long long llDamage) override;
	virtual void OnDead() override;

private:
};

