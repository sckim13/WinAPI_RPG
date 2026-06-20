#include "pch.h"
#include "CEquipItem.h"
#include "CTexture.h"
#include "CTransform.h"
#include "CCollider.h"
#include "CResourceManager.h"

CEquipItem::CEquipItem()
{
}

CEquipItem::~CEquipItem()
{
}

void CEquipItem::Initialize()
{
	__super::Initialize();

	m_eItemType = EItemType::EQUIP;
	m_eEquipSlot = EEquipSlot::SHOES;

	m_pTexture = CResourceManager::GetInstance()->LoadTexture(L"Item", L"Texture\\Item.bmp");
	m_pTexture->SetOwner(this);
	m_pCollider = new CCollider;
	m_pCollider->Initialize();
	m_pCollider->SetOwner(this);
}

void CEquipItem::PostInitialize()
{
}

void CEquipItem::Update()
{
}

void CEquipItem::LateUpdate()
{
	if (GetOwner())
	{
		SetPosition(GetOwner()->GetPosition());
	}

	GetCollider()->LateUpdate();
}

void CEquipItem::Release()
{
}

void CEquipItem::Render(HDC hDC)
{
	if (GetOwner()) return;

	GetTexture()->Render(hDC, (int)GetPosition().x, (int)GetPosition().y);

	GetCollider()->Render(hDC);
}
