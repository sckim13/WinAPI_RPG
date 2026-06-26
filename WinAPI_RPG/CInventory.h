#pragma once

#include "CComponent.h"

class CItem;

template<typename T>
class CEventDelegate;

class CInventory : public CComponent
{
public:
	CInventory();
	virtual ~CInventory();

	virtual void Initialize() override;
	void ClearItemContainer();
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	void PushItem(CItem* pItem);
	void PopItem(CItem* pItem);

	void Pack(EInventoryTab eTab);
	void Sort(EInventoryTab eTab);
	bool Compare(EInventoryTab eTab, CItem* lhs, CItem* rhs);

	CEventDelegate<TInventoryCtx>* m_OnInventoryUpdated;
private:
	array<array<CItem*, MAX_INVENTORY_SIZE>, (int)EInventoryTab::MAX> m_pItemContainer;
	EInventoryTab m_eCurrentTab;

	array<array<const CItem*, MAX_INVENTORY_SIZE>, (int)EInventoryTab::MAX> CaptureInventory();

public:
	inline CItem* GetItemByIndex(EInventoryTab eTab, int iIndex) { return m_pItemContainer[(int)eTab][iIndex]; }

};

