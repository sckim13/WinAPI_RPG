#pragma once

#include "CComponent.h"

class CItem;

class CEquipment : public CComponent
{
public:
	CEquipment();
	virtual ~CEquipment();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	void Equip(CItem* pItem);
	void UnEquip(EEquipSlot eSlot);

	CEventHandle<TEquipmentCtx>* m_hOnEquipmentUpdated;

private:
	array<CItem*, (int)EEquipSlot::MAX> m_arrEquipSlot;

	array<const CItem*, (int)EEquipSlot::MAX> CaptureSlot();

public:
	CItem* GetItemBySlot(EEquipSlot eSlot) { return m_arrEquipSlot[(int)eSlot]; }
};

