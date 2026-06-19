#pragma once

#include "CComponent.h"

class CItem;
struct TInventoryCtx;

template<typename T>
class CEventHandle;

class CInventory : public CComponent
{
public:
	CInventory();
	virtual ~CInventory();

	void Initialize() override;
	void PostInitialize() override;
	void Update() override;
	void LateUpdate() override;
	void Release() override;
	void Render(HDC hDC) override;

	void PushItem(CItem* pItem);
	void PopItem(CItem* pItem);

	void Pack(EInventoryTab eTab);
	void Sort(EInventoryTab eTab);
	bool Compare(EInventoryTab eTab, CItem* lhs, CItem* rhs);

	CEventHandle<TInventoryCtx>* m_hOnInventoryUpdated;
private:
	array<array<CItem*, MAX_INVENTORY_SIZE>, (int)EInventoryTab::MAX> m_pItemContainer;

	EInventoryTab m_eCurrentTab;

};

