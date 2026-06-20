#include "pch.h"
#include "CEquipment.h"
#include "CItem.h"
#include "CEquipItem.h"
#include "CInventory.h"
#include "CPlayer.h"

CEquipment::CEquipment() : m_arrEquipSlot{}
{
}

CEquipment::~CEquipment()
{
}

void CEquipment::Initialize()
{
	m_hOnEquipmentUpdated = new CEventHandle<TEquipmentCtx>;
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
	if (m_arrEquipSlot[(int)eEquipSlot])
	{
		UnEquip(eEquipSlot);
	}
	m_arrEquipSlot[(int)eEquipSlot] = pEquipItem;

	m_hOnEquipmentUpdated->Broadcast(TEquipmentCtx{ CaptureSlot() });
}

void CEquipment::UnEquip(EEquipSlot eSlot)
{
	CItem* pItem = m_arrEquipSlot[(int)eSlot];

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwner());
	assert(pPlayer);
	pPlayer->GetInventory()->PushItem(pItem);

	m_hOnEquipmentUpdated->Broadcast(TEquipmentCtx{ CaptureSlot() });
}

array<const CItem*, (int)EEquipSlot::MAX> CEquipment::CaptureSlot()
{
	array<const CItem*, (int)EEquipSlot::MAX> arrCapture;
	copy(m_arrEquipSlot.begin(), m_arrEquipSlot.end(), arrCapture.begin());
	return arrCapture;
}
