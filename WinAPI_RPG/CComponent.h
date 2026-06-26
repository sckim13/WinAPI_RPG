#pragma once

#include "CBase.h"

class CObject;
class CUI;

class CComponent : public CBase
{
public:
	CComponent();
	virtual ~CComponent() PURE;

	virtual void Initialize() PURE;
	virtual void PostInitialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Release() PURE;
	virtual void Render(HDC hDC) PURE;

	void AttachTo(CObject* pObject); // must be called after allocating the component in object

private:
	CObject* m_pOwner;

public:
	inline void SetOwner(CObject* pOwner) { m_pOwner = pOwner; }
	inline CObject* GetOwner() { return m_pOwner; }

};

