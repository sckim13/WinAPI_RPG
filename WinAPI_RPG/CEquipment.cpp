#include "pch.h"
#include "CEquipment.h"
#include "CItem.h"
#include "CEquipItem.h"

CEquipment::CEquipment()
{
}

CEquipment::~CEquipment()
{
}

void CEquipment::Initialize()
{
}

void CEquipment::PostInitialize()
{
}

void CEquipment::Update()
{
}

void CEquipment::LateUpdate()
{
}

void CEquipment::Release()
{
}

void CEquipment::Render(HDC hDC)
{
}

void CEquipment::Equip(CItem* pItem)
{
	CEquipItem* pEquipItem = dynamic_cast<CEquipItem*>(pItem);
	assert(pEquipItem);

	EEquipSlot eEquipSlot = pEquipItem->GetEquipSlot();
	if (m_EquipSlot[(int)eEquipSlot])
	{
		UnEquip(eEquipSlot);
	}
	m_EquipSlot[(int)eEquipSlot] = pEquipItem;
}

void CEquipment::UnEquip(EEquipSlot eSlot)
{
	m_EquipSlot[(int)eSlot] = nullptr;

	/* TODO : push unequipped item to the inventory */
}
