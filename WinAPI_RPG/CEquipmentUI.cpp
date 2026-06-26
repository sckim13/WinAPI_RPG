#include "pch.h"
#include "CEquipmentUI.h"
#include "CSceneManager.h"
#include "CPlayer.h"
#include "CEquipment.h"
#include "CResourceManager.h"
#include "CTextureComponent.h"
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

	m_pMainTexture = new CTextureComponent;
	m_pMainTexture->AttachTo(this);
	m_pMainTexture->BindTexture(L"Equipment");
}

void CEquipmentUI::PostInitialize()
{
	CSceneManager::GetInstance()->GetPlayer()->GetEquipment()->m_OnEquipmentUpdated->AddBinding(
		GetID(), [this](TEquipmentCtx Ctx) { OnEquipmentUpdated(Ctx); }
	);
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

	m_pMainTexture->Render(hDC);

	for (int i = 0; i < (int)EEquipSlot::MAX; ++i)
	{
		if (const CItem* pItem = m_arrEquipSlot[i])
		{
			pItem->GetTextureComponent()->Render(hDC, (int)m_pDummyItemRect.x, (int)m_pDummyItemRect.y);
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

void CEquipmentUI::OnEquipmentUpdated(const TEquipmentCtx& Ctx)
{
	auto [arrEquipSlot] = Ctx;

	m_arrEquipSlot = arrEquipSlot;
}

void CEquipmentUI::OnKeyEventTriggered(const TKeyEventCtx& Ctx)
{
	auto [eKeyEvent, eKeyState] = Ctx;

	if (eKeyState != EKeyState::PRESSED) return;

	if (eKeyEvent == EEventType::UI_EQUIPMENT)
	{
		ToggleVisibility();
		OnFocused();
	}
}

bool CEquipmentUI::IsCursorOnUI(Vec2 vCursorPos)
{
	return MathUtil::IsPointInRect(vCursorPos - GetPosition(), Vec2{ 0, 0 }, m_pMainTexture->GetTextureSize());
}


void CEquipmentUI::OnMouseEventTriggered(const TMouseEventCtx& Ctx)
{
	__super::OnMouseEventTriggered(Ctx);

	auto [eKey, eKeyState, vCursorPos] = Ctx;
	// cout << magic_enum::enum_name(eKey) << ", " << magic_enum::enum_name(eKeyState) << ", (" << vCursorPos.x << ", " << vCursorPos.y << ")" << endl;
	if (eKey == EKey::L_CLICK
		&& eKeyState == EKeyState::DOUBLE_PRESSED
		&& MathUtil::IsPointInRect(vCursorPos, m_pDummyItemRect, m_pDummyItemRect + Vec2{ 100.f, 100.f }))
	{
		cout << "[Equipment UI] Item UnEquip event" << endl;
		CItemManager::GetInstance()->RequestUnEquipItem(EEquipSlot::HEAD);
	}
}