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
	Release();
}

void CEquipmentUI::Initialize()
{
	SetUIType(EUIType::EQUIPMENT);

	m_pMainTexture = new CTextureComponent;
	m_pMainTexture->AttachTo(this);
	m_pMainTexture->BindTexture(L"Equipment");
	m_pMainTexture->SetScrollEnabled(false);
	
	__super::Initialize();
}

void CEquipmentUI::PostInitialize()
{
	CSceneManager::GetInstance()->GetPlayer()->GetEquipment()->m_OnEquipmentUpdated->AddBinding(
		GetID(), [this](TEquipmentCtx Ctx) { OnEquipmentUpdated(Ctx); }
	);

	__super::PostInitialize();
}

void CEquipmentUI::Update()
{
}

void CEquipmentUI::LateUpdate()
{
}

void CEquipmentUI::Release()
{
	CSceneManager::GetInstance()->GetPlayer()->GetEquipment()->m_OnEquipmentUpdated->DeleteBinding(GetID());
}

void CEquipmentUI::Render(HDC hDC)
{
	if (!IsVisible()) return;

	m_pMainTexture->Render(hDC);

	for (int i = 0; i < (int)EEquipSlot::MAX; ++i)
	{
		if (const CItem* pItem = m_arrEquipSlot[i])
		{
			pItem->GetTextureComponent()->Render(hDC, (int)(GetPosition().x) + m_ptDummyItemRect.x, (int)(GetPosition().y) + m_ptDummyItemRect.y);
		}
	}

	/* move area rectangle */
	__super::Render(hDC);
}

bool CEquipmentUI::IsValidInput(IPoint ptCursorPos)
{
	if (!__super::IsValidInput(ptCursorPos)) return false;

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

bool CEquipmentUI::IsCursorOnUI(const IPoint& ptCursorPos)
{
	return MathUtil::IsPointInRect(ptCursorPos, IPoint(GetPosition()), m_pMainTexture->GetTextureSize());
}


void CEquipmentUI::OnMouseEventTriggered(const TMouseEventCtx& Ctx)
{
	__super::OnMouseEventTriggered(Ctx);

	auto [eKey, eKeyState, vCursorPos] = Ctx;
	// cout << magic_enum::enum_name(eKey) << ", " << magic_enum::enum_name(eKeyState) << ", (" << vCursorPos.x << ", " << vCursorPos.y << ")" << endl;
	if (eKey == EKey::L_CLICK
		&& eKeyState == EKeyState::DOUBLE_PRESSED
		&& MathUtil::IsPointInRect(vCursorPos - IPoint(GetPosition()), m_ptDummyItemRect, m_ptDummyItemRect + IPoint{ 100, 100 }))
	{
		cout << "[Equipment UI] Item UnEquip event" << endl;
		CItemManager::GetInstance()->RequestUnEquipItem(EEquipSlot::HEAD);
	}
}