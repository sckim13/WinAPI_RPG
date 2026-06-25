#pragma once

#include "CObject.h"

class CItem : public CObject
{
public:
	CItem();
	virtual ~CItem();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) PURE;


protected:
	EItemType m_eItemType;
private:
	int m_iBuyPrice;
	int m_iSellPrice;
	
	bool m_bCashItem;

	CObject* m_pOwner;

public:
	inline EItemType GetItemType() const { return m_eItemType; }
	// inline bool IsOnField() { return m_bOnField; }

	inline void SetOwner(CObject* pObj) { m_pOwner = pObj; }
	inline CObject* GetOwner() { return m_pOwner; } 
};

