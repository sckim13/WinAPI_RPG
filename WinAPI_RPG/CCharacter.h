#pragma once

#include "CObject.h"
#include "ICollide.h"
#include "ICombat.h"

class CTexture;
class CCollider;
class CTransform;
class CController;
class CMovementComponent;

class CCharacter : public CObject, public ICollide, public ICombat
{
public:
	CCharacter();
	virtual ~CCharacter() PURE;

	virtual void Initialize() override;
	virtual void PostInitialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Release() PURE;
	virtual void Render(HDC hDC) PURE;

	/* ICollide */
	virtual void OnCollisionBegin(const TCollisionCtx& Ctx) override;
	virtual void OnCollision(const TCollisionCtx& Ctx) override;
	virtual void OnCollisionEnd(const TCollisionCtx& Ctx) override;

	/* ICombat */
	virtual void OnHit(long long llDamage) PURE;
	virtual void OnDead() PURE;

protected:
	long long m_llHP;
	long long m_llMaxHP;
	CMovementComponent* m_pMovementComponent;

private:
	// CController* m_pController;

public:
	// inline void SetController(CController* pCtrl) { m_pController = pCtrl; }
	// inline CController* GetController() { return m_pController; }

};

