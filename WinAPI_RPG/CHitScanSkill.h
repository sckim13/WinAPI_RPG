#pragma once

#include "CActiveSkill.h"

class CHitScanSkill : public CActiveSkill
{
public:
	CHitScanSkill();
	virtual ~CHitScanSkill();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	virtual void Execute() override;

	virtual void OnCollisionBegin(TCollisionCtx Ctx) override;
	virtual void OnCollision(TCollisionCtx Ctx) override;
	virtual void OnCollisionEnd(TCollisionCtx Ctx) override;
};

