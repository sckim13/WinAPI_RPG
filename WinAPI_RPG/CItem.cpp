#include "pch.h"
#include "CItem.h"

CItem::CItem() : m_pOwner(nullptr)
{
}

CItem::~CItem()
{
}

void CItem::Initialize()
{
	__super::Initialize();

	m_eObjectType = EObjectType::ITEM;

	wstring wstrName = L"Item_" + to_wstring(GetID());
	SetName(wstrName);
}
