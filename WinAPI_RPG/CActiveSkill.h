#pragma once

#include "CSkill.h"
#include "ICollide.h"

class CAnimator;

class CActiveSkill : public CSkill, public ICollide
{
public:
	CActiveSkill();
	virtual ~CActiveSkill();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	virtual void Execute() PURE;

	virtual void OnCollisionBegin(const TCollisionCtx& Ctx) override;
	virtual void OnCollision(const TCollisionCtx& Ctx) override;
	virtual void OnCollisionEnd(const TCollisionCtx& Ctx) override;

protected:
	CAnimator* m_pAnimator;
};

