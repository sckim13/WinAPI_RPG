#pragma once

#include "CComponent.h"

class CTransform;
struct TCollisionCtx;

template<typename T>
class CEventHandle;

class CCollider : public CComponent
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

	void OnCollisionBegin(CCollider * pCounterPart);
	void OnCollision(CCollider* pCounterPart);
	void OnCollisionEnd(CCollider* pCounterPart);

	static INT32 g_ID;

	CEventHandle<TCollisionCtx>* m_hOnCollisionBegin;
	CEventHandle<TCollisionCtx>* m_hOnCollisionEnd;


private:

	CTransform* m_pTransform;

	int m_iCollisionCount;

	RECT m_rcCollision;

	void UpdateRect();

	vector<CCollider*> m_vecPrevCollided;

	vector<CCollider*> m_vecColliding;

	INT32 m_ID;

	bool m_bEnabled;


public:
	inline CTransform* GetTransform() { return m_pTransform; }
	inline RECT* GetRect() { return &m_rcCollision; }
	inline INT32 GetID() { return m_ID; }
	void SetEnabled(bool bEnabled) { m_bEnabled = bEnabled; }
	bool IsEnabled() { return m_bEnabled; }
};

