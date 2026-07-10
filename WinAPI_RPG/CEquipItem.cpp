#include "pch.h"
#include "CEquipItem.h"
#include "CTextureComponent.h"
#include "CTransform.h"
#include "CCollider.h"
#include "CResourceManager.h"

CEquipItem::CEquipItem()
{
}

CEquipItem::~CEquipItem()
{
	Release();
}

void CEquipItem::Initialize()
{
	m_eItemType = EItemType::EQUIP;
	m_eEquipSlot = EEquipSlot::HEAD;

	m_pTextureComponent = new CTextureComponent;
	m_pTextureComponent->AttachTo(this);
	m_pTextureComponent->BindTexture(L"Item");

	m_pCollider = new CCollider;
	m_pCollider->AttachTo(this);

	__super::Initialize();
}

void CEquipItem::PostInitialize()
{
	__super::PostInitialize();
}

void CEquipItem::Update()
{
	__super::Update();
}

void CEquipItem::LateUpdate()
{
	__super::LateUpdate();
}

void CEquipItem::Release()
{
	__super::Release();
}

void CEquipItem::Render(HDC hDC)
{
	if (GetOwner()) return;

	GetTextureComponent()->Render(hDC);

	GetCollider()->Render(hDC);
}
