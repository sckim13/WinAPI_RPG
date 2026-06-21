#include "pch.h"
#include "CEquipmentUI.h"
#include "CSceneManager.h"
#include "CPlayer.h"
#include "CEquipment.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CItem.h"
#include "MathUtil.h"
#include "CItemManager.h"

CEquipmentUI::CEquipmentUI() : m_pMainTexture(nullptr)
{
}

CEquipmentUI::~CEquipmentUI()
{
}

void CEquipmentUI::Initialize()
{
	__super::Initialize();

	SetUIType(EUIType::EQUIPMENT);

	m_pMainTexture = CResourceManager::GetInstance()->LoadTexture(L"Equipment", L"Texture\\Equipment.bmp");

	CSceneManager::GetInstance()->GetPlayer()->GetEquipment()->m_hOnEquipmentUpdated->AddBinding(
		this, [this](TEquipmentCtx Ctx) { OnEquipmentUpdated(Ctx); }
	);
}

void CEquipmentUI::PostInitialize()
{
}

void CEquipmentUI::Update()
{
}

void CEquipmentUI::LateUpdate()
{
}

void CEquipmentUI::Release()
{
}

void CEquipmentUI::Render(HDC hDC)
{
	if (!IsVisible()) return;

	m_pMainTexture->Render(hDC, (int)GetPosition().x, (int)GetPosition().y);

	for (int i = 0; i < (int)EEquipSlot::MAX; ++i)
	{
		if (const CItem* pItem = m_arrEquipSlot[i])
		{
			pItem->GetTexture()->Render(hDC, (int)(GetPosition().x + m_pDummyItemRect.x), (int)(GetPosition().y + m_pDummyItemRect.y));
		}
	}

	/* move area rectangle */
	__super::Render(hDC);
}

bool CEquipmentUI::IsValidInput(Vec2 vCursorPos)
{
	if (!__super::IsValidInput(vCursorPos)) return false;

	return true;
}

void CEquipmentUI::OnEquipmentUpdated(TEquipmentCtx Ctx)
{
	auto [arrEquipSlot] = Ctx;

	m_arrEquipSlot = arrEquipSlot;
}

void CEquipmentUI::OnKeyEventTriggered(TKeyEventCtx Ctx)
{
	auto [eKeyEvent, eKeyState] = Ctx;

	if (eKeyEvent == EEventType::UI_EQUIPMENT)
	{
		ToggleVisibility();
		OnFocused();
	}
}

bool CEquipmentUI::IsCursorOnUI(Vec2 vCursorPos)
{
	return MathUtil::IsPointInRect(vCursorPos, GetPosition(), m_pMainTexture->GetSize());
}


void CEquipmentUI::OnMouseEventTriggered(TMouseEventCtx Ctx)
{
	__super::OnMouseEventTriggered(Ctx);

	auto [eKey, eKeyState, vCursorPos] = Ctx;

	if (eKey == EKey::L_CLICK
		&& eKeyState == EKeyState::DOUBLE_PRESSED
		&& MathUtil::IsPointInRect(vCursorPos, m_pDummyItemRect, m_pDummyItemRect + Vec2{ 100.f, 100.f }))
	{
		cout << "[Equipment UI] Item UnEquip event" << endl;
		CItemManager::GetInstance()->RequestUnEquipItem(EEquipSlot::HEAD);
	}
}