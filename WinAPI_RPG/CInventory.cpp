#include "pch.h"
#include "CInventory.h"
#include "CItem.h"
#include "CEquipItem.h"


CInventory::CInventory()
{
}

CInventory::~CInventory()
{
}

void CInventory::Initialize()
{
}

void CInventory::PostInitialize()
{
}

void CInventory::Update()
{
}

void CInventory::LateUpdate()
{
}

void CInventory::Release()
{
}

void CInventory::Render(HDC hDC)
{
}

void CInventory::PushItem(CItem* pItem)
{
	/* add item to the empty container with ascending order */
	EItemType eItemType = pItem->GetItemType();
	for (int i = 0; i < MAX_INVENTORY_SIZE; ++i)
	{
		if (m_pItemContainer[(int)eItemType][i] == nullptr)
		{
			m_pItemContainer[(int)eItemType][i] = pItem;
			return;
		}
	}
	assert(0);
}

void CInventory::PopItem(CItem* pItem)
{
	EItemType eItemType = pItem->GetItemType();
	for (int i = 0; i < MAX_INVENTORY_SIZE; ++i)
	{
		if (m_pItemContainer[(int)eItemType][i] == pItem)
		{
			m_pItemContainer[(int)eItemType][i] = nullptr;
			return;
		}
	}
	assert(0);
}

void CInventory::Pack(EInventoryTab eTab)
{
	priority_queue<int, vector<int>, greater<int>> pq;

	for (int i = 0; i < MAX_INVENTORY_SIZE; ++i)
	{
		if (m_pItemContainer[(int)eTab][i] == nullptr)
		{
			pq.push(i);
		}
		else
		{
			if (!pq.empty())
			{
				int iIdx = pq.top();
				m_pItemContainer[(int)eTab][iIdx] = m_pItemContainer[(int)eTab][i];
				pq.pop();
				pq.push(i);
			}
		}
	}
}

void CInventory::Sort(EInventoryTab eTab)
{
	sort(m_pItemContainer[(int)eTab].begin(), m_pItemContainer[(int)eTab].end(),
		[this, eTab] (CItem*& lhs, CItem*& rhs)
		{
			return Compare(eTab, lhs, rhs);
		}
	);
}

bool CInventory::Compare(EInventoryTab eTab, CItem* lhs, CItem* rhs)
{
	switch (eTab)
	{
	case EInventoryTab::EQUIP:
	{
		CEquipItem* _lhs = static_cast<CEquipItem*>(lhs);
		CEquipItem* _rhs = static_cast<CEquipItem*>(rhs);
		return (int)_lhs->GetEquipSlot() < (int)_rhs->GetEquipSlot();
	}
	case EInventoryTab::CONSUME:
	case EInventoryTab::SETUP:
	case EInventoryTab::MISC:
	default:
		assert(0);
		return false;
	}
}
