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
	Release();
}

void CEquipItem::Initialize()
{
	__super::Initialize();

	m_eItemType = EItemType::EQUIP;
	m_eEquipSlot = EEquipSlot::HEAD;

	m_pTexture = CResourceManager::GetInstance()->LoadTexture(L"Item", L"Texture\\Item.bmp");
	m_pTexture->AttachTo(this);

	m_pCollider = new CCollider;
	m_pCollider->AttachTo(this);
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

	if (GetOwner())
	{
		SetPosition(GetOwner()->GetPosition());
	}
}

void CEquipItem::Release()
{
	__super::Release();
}

void CEquipItem::Render(HDC hDC)
{
	if (GetOwner()) return;

	GetTexture()->Render(hDC, (int)GetPosition().x, (int)GetPosition().y);

	GetCollider()->Render(hDC);
}
