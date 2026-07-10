#include "pch.h"
#include "CItem.h"

CItem::CItem() : m_pOwner(nullptr)
{
}

CItem::~CItem()
{
	Release();
}

void CItem::Initialize()
{
	m_eObjectType = EObjectType::ITEM;

	wstring wstrName = L"Item_" + to_wstring(GetID());
	SetName(wstrName);

	__super::Initialize();
}

void CItem::PostInitialize()
{
	__super::PostInitialize();
}

void CItem::Update()
{
	__super::Update();
}

void CItem::LateUpdate()
{
	__super::LateUpdate();
}

void CItem::Release()
{
	__super::Release();
}
