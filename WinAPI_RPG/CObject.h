#pragma once

#include "CBase.h"

class CTransform;
class CTexture;
class CCollider;
class CComponent;

class CObject : public CBase
{
public:
	CObject();
	virtual ~CObject() PURE;

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

protected:
	CTransform* m_pTransform;
	CTexture* m_pTexture;
	CCollider* m_pCollider;

public:
	inline CTransform* GetTransform() { return m_pTransform; }
	inline CTexture* GetTexture() { return m_pTexture; }
	inline CCollider* GetCollider() { return m_pCollider; }
};

