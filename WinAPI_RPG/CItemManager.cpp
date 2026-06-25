#include "pch.h"
#include "CItemManager.h"
#include "CPlayer.h"
#include "CInventory.h"
#include "CEquipment.h"
#include "CEquipItem.h"

CItemManager::CItemManager()
{
}

CItemManager::~CItemManager()
{
}

void CItemManager::Initialize()
{
}

void CItemManager::PostInitialize()
{
}

void CItemManager::Update()
{
}

void CItemManager::LateUpdate()
{
}

void CItemManager::Release()
{
}

void CItemManager::Render(HDC hDC)
{
}

void CItemManager::RequestEquipItem(EInventoryTab eTab, int iIdx)
{
	CItem* pItem = GetPlayer()->GetInventory()->GetItemByIndex(eTab, iIdx);
	CEquipItem* pEquipItem = dynamic_cast<CEquipItem*>(pItem);
	
	// assert(pEquipItem);

	GetPlayer()->GetInventory()->PopItem(pItem);
	GetPlayer()->GetEquipment()->Equip(pItem);
}

void CItemManager::RequestUnEquipItem(EEquipSlot eSlot)
{
	if (GetPlayer()->GetEquipment()->GetItemBySlot(eSlot))
	{
		GetPlayer()->GetEquipment()->UnEquip(eSlot);
	}
	else
	{
		cout << "No Item Equipped in slot " << magic_enum::enum_name(eSlot) << endl;
	}
}

void CItemManager::RequestPushItem(CItem* pItem)
{
	GetPlayer()->GetInventory()->PushItem(pItem);
}
