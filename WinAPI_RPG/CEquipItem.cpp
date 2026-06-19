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
	GetCollider()->LateUpdate();
}

void CEquipItem::Release()
{
}

void CEquipItem::Render(HDC hDC)
{
	if (GetOwner())
	{
		int iWidth = (int)GetTexture()->GetWidth();
		int iHeight = (int)GetTexture()->GetHeight();

		Vec2 vPos = GetPosition();

		StretchBlt(
			hDC,
			(int)(vPos.x - (float)(iWidth / 2)),
			(int)(vPos.y - (float)(iHeight / 2)),
			iWidth, iHeight,
			GetTexture()->GetDC(),
			0, 0, iWidth, iHeight,
			SRCCOPY);
	}

	GetCollider()->Render(hDC);
}
