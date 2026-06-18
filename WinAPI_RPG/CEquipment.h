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

private:
	CItem* m_EquipSlot[(int)EEquipSlot::MAX];

};

