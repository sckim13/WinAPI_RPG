#include "pch.h"
#include "CInventoryUI.h"
#include "CInventory.h"
#include "EventContext.h"
#include "CResourceManager.h"
#include "CTextureComponent.h"
#include "CSceneManager.h"
#include "CPlayer.h"
#include "CItem.h"
#include "CCollider.h"
#include "MathUtil.h"
#include "CItemManager.h"

CInventoryUI::CInventoryUI()
{
}

CInventoryUI::~CInventoryUI()
{
	Release();
}

void CInventoryUI::Initialize()
{
	__super::Initialize();

	SetUIType(EUIType::INVENTORY);

	m_pMainTexture = new CTextureComponent;
	m_pMainTexture->AttachTo(this);
	m_pMainTexture->BindTexture(L"Inventory");
}

void CInventoryUI::PostInitialize()
{
	__super::PostInitialize();

	CSceneManager::GetInstance()->GetPlayer()->GetInventory()->m_OnInventoryUpdated->AddBinding(
		GetID(), 
		[this](const TInventoryCtx& Ctx) { OnInventoryUpdated(Ctx); }
	);
}

void CInventoryUI::Update()
{
}

void CInventoryUI::LateUpdate()
{
}

void CInventoryUI::Release()
{
	CSceneManager::GetInstance()->GetPlayer()->GetInventory()->m_OnInventoryUpdated->DeleteBinding(GetID());
}

void CInventoryUI::Render(HDC hDC)
{
	if (!IsVisible()) return;

	m_pMainTexture->Render(hDC);

	for (int i = 0; i < MAX_INVENTORY_SIZE; ++i)
	{
		if (const CItem* pItem = m_arrItem[(int)m_eCurrentTab][i])
		{
			pItem->GetTextureComponent()->Render(hDC, (int)(GetPosition().x + m_pDummyItemRect.x), (int)(GetPosition().y + m_pDummyItemRect.y));
		}
	}

	/* move area rectangle */
	__super::Render(hDC);
}

void CInventoryUI::OnInventoryUpdated(const TInventoryCtx& Ctx)
{
	wcout << "[Inventory UI] Update Inventory UI" << endl;

	// array<array<CItem*, MAX_INVENTORY_SIZE>, (int)EInventoryTab::MAX>* arrItem;
	// EInventoryTab eCurrentTab;
	auto [arrItem, eCurrentTab] = Ctx;

	m_eCurrentTab = eCurrentTab;
	m_arrItem = arrItem;
}

bool CInventoryUI::IsValidInput(Vec2 vCursorPos)
{
	if(!__super::IsValidInput(vCursorPos)) return false;

	return true;
}

void CInventoryUI::OnKeyEventTriggered(const TKeyEventCtx& Ctx)
{
	auto [eKeyEvent, eKeyState] = Ctx;

	if (eKeyState != EKeyState::PRESSED) return;

	if (eKeyEvent == EEventType::UI_INVENTORY)
	{
		ToggleVisibility();
		OnFocused();
	}
}

void CInventoryUI::OnMouseEventTriggered(const TMouseEventCtx& Ctx)
{
	__super::OnMouseEventTriggered(Ctx);

	auto [eKey, eKeyState, vCursorPos] = Ctx;

	if (eKey == EKey::L_CLICK
		&& eKeyState == EKeyState::DOUBLE_PRESSED
		&& MathUtil::IsPointInRect(vCursorPos - GetPosition(), m_pDummyItemRect, m_pDummyItemRect + Vec2{100.f, 100.f}))
	{
		cout << "[Inventory UI] Item Equip event" << endl;
		CItemManager::GetInstance()->RequestEquipItem(m_eCurrentTab, 0);
	}
}

bool CInventoryUI::IsCursorOnUI(Vec2 vCursorPos)
{
	return MathUtil::IsPointInRect(vCursorPos, GetPosition(), m_pMainTexture->GetTextureSize());
}
