#pragma once

#include "CComponent.h"
#include "ICollide.h"
#include "CTransform.h"

struct TCollisionCtx;

template<typename T>
class CEventDelegate;

class CCollider : public CComponent, public ICollide
{
public:
	CCollider();
	virtual ~CCollider();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	/* ICollide */
	virtual void OnCollisionBegin(const TCollisionCtx& Ctx) override;
	virtual void OnCollision(const TCollisionCtx& Ctx) override;
	virtual void OnCollisionEnd(const TCollisionCtx& Ctx) override;

	CEventDelegate<TCollisionCtx>* m_OnCollisionBegin;
	CEventDelegate<TCollisionCtx>* m_OnCollisionEnd;


private:

	CTransform m_Transform;

	int m_iCollisionCount;

	RECT m_rcCollision;

	void UpdateRect();

	vector<CCollider*> m_vecPrevCollided;

	vector<CCollider*> m_vecColliding;

	bool m_bEnabled;


public:
	inline CTransform* GetTransform() { return &m_Transform; }
	inline RECT* GetRect() { return &m_rcCollision; }
	void SetEnabled(bool bEnabled) { m_bEnabled = bEnabled; }
	bool IsEnabled() { return m_bEnabled; }
};

