#include "pch.h"
#include "CItemManager.h"
#include "CPlayer.h"
#include "CInventory.h"
#include "CEquipment.h"
#include "CEquipItem.h"
#include "CSceneManager.h"

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
	CPlayer* pPlayer = CSceneManager::GetInstance()->GetPlayer();
	CItem* pItem = pPlayer->GetInventory()->GetItemByIndex(eTab, iIdx);
	CEquipItem* pEquipItem = dynamic_cast<CEquipItem*>(pItem);
	
	// assert(pEquipItem);

	pPlayer->GetInventory()->PopItem(pItem);
	pPlayer->GetEquipment()->Equip(pItem);
}

void CItemManager::RequestUnEquipItem(EEquipSlot eSlot)
{
	CPlayer* pPlayer = CSceneManager::GetInstance()->GetPlayer();
	if (pPlayer->GetEquipment()->GetItemBySlot(eSlot))
	{
		pPlayer->GetEquipment()->UnEquip(eSlot);
	}
	else
	{
		cout << "No Item Equipped in slot " << magic_enum::enum_name(eSlot) << endl;
	}
}

void CItemManager::RequestPushItem(CItem* pItem)
{
	CPlayer* pPlayer = CSceneManager::GetInstance()->GetPlayer();
	pPlayer->GetInventory()->PushItem(pItem);
}
