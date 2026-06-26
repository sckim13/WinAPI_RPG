#include "pch.h"
#include "CEquipment.h"
#include "CItem.h"
#include "CEquipItem.h"
#include "CInventory.h"
#include "CPlayer.h"
#include "CItemManager.h"

CEquipment::CEquipment() : m_arrEquipSlot{}
{
}

CEquipment::~CEquipment()
{
	Release();
}

void CEquipment::Initialize()
{
	m_OnEquipmentUpdated = new CEventDelegate<TEquipmentCtx>;
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
	Safe_Delete<CEventDelegate<TEquipmentCtx>*>(m_OnEquipmentUpdated);
}

void CEquipment::Render(HDC hDC)
{
}

void CEquipment::Equip(CItem* pItem)
{
	CEquipItem* pEquipItem = dynamic_cast<CEquipItem*>(pItem);
	assert(pEquipItem);

	EEquipSlot eEquipSlot = pEquipItem->GetEquipSlot();
	if (m_arrEquipSlot[(int)eEquipSlot])
	{
		UnEquip(eEquipSlot);
	}
	m_arrEquipSlot[(int)eEquipSlot] = pEquipItem;

	m_OnEquipmentUpdated->Broadcast(TEquipmentCtx{ CaptureSlot() });
}

void CEquipment::UnEquip(EEquipSlot eSlot)
{
	CItem* pItem = m_arrEquipSlot[(int)eSlot];

	CItemManager::GetInstance()->RequestPushItem(pItem);

	m_arrEquipSlot[(int)eSlot] = nullptr;

	m_OnEquipmentUpdated->Broadcast(TEquipmentCtx{ CaptureSlot() });
}

array<const CItem*, (int)EEquipSlot::MAX> CEquipment::CaptureSlot()
{
	array<const CItem*, (int)EEquipSlot::MAX> arrCapture;
	copy(m_arrEquipSlot.begin(), m_arrEquipSlot.end(), arrCapture.begin());
	return arrCapture;
}
