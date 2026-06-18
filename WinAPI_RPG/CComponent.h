#pragma once

#include "CBase.h"

class CObject;

class CComponent : public CBase
{
public:
	CComponent();
	virtual ~CComponent() PURE;

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

private:
	CObject* m_pOwner;

public:
	inline void SetOwner(CObject* pOwner) { m_pOwner = pOwner; }
	inline CObject* GetOwner() { return m_pOwner; }

};

