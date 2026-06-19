#pragma once

#include "CBase.h"
#include "CTransform.h"

class CTexture;
class CCollider;
class CComponent;

class CObject : public CBase
{
public:
	CObject();
	virtual ~CObject() PURE;

	virtual void Initialize() PURE;
	virtual void PostInitialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Release() PURE;
	virtual void Render(HDC hDC) PURE;

protected:
	CTexture* m_pTexture;
	CCollider* m_pCollider;
	EObjectType m_eObjectType;

public:
	inline CTexture* GetTexture() { return m_pTexture; }
	inline CCollider* GetCollider() { return m_pCollider; }
	inline EObjectType GetObjectType() { return m_eObjectType; }
};

