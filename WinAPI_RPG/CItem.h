#pragma once

#include "CObject.h"

class CItem : public CObject
{
public:
	CItem();
	virtual ~CItem();

	virtual void Initialize() PURE;
	virtual void PostInitialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Release() PURE;
	virtual void Render(HDC hDC) PURE;

private:
	EItemType m_eItemType;

	int m_iBuyPrice;
	int m_iSellPrice;
	
	bool m_bCashItem;

public:
	inline EItemType GetItemType() { return m_eItemType; }
};

