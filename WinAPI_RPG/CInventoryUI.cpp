#include "pch.h"
#include "CInventoryUI.h"
#include "CInventory.h"
#include "CEventHandle.h"
#include "EventContext.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CSceneManager.h"
#include "CPlayer.h"
#include "CItem.h"
#include "CCollider.h"

CInventoryUI::CInventoryUI()
{
}

CInventoryUI::~CInventoryUI()
{
}

void CInventoryUI::Initialize()
{
	__super::Initialize();

	m_pMainTexture = CResourceManager::GetInstance()->LoadTexture(L"Inventory", L"Texture\\Inventory.bmp");
	CSceneManager::GetInstance()->GetPlayer()->GetInventory()->m_hOnInventoryUpdated->AddBinding(this, [this](TInventoryCtx Ctx) { OnInventoryUpdated(Ctx); });

	m_pFirstItemCollider = new CCollider;
	m_pFirstItemCollider->Initialize();
	m_pFirstItemCollider->SetPosition(Vec2{ 100.f, 100.f });
}

void CInventoryUI::PostInitialize()
{
}

void CInventoryUI::Update()
{
}

void CInventoryUI::LateUpdate()
{
}

void CInventoryUI::Release()
{
}

void CInventoryUI::Render(HDC hDC)
{
	if (!IsVisible()) return;

	m_pMainTexture->Render(hDC, (int)GetPosition().x, (int)GetPosition().y);

	for (int i = 0; i < MAX_INVENTORY_SIZE; ++i)
	{
		if (const CItem* pItem = m_arrItem[(int)m_eCurrentTab][i])
		{
			pItem->GetTexture()->Render(hDC, (int)GetPosition().x + 100, (int)GetPosition().y + 100);
		}
	}
}

void CInventoryUI::OnInventoryUpdated(TInventoryCtx Ctx)
{
	wcout << "[Inventory UI] Update Inventory UI" << endl;

	// array<array<CItem*, MAX_INVENTORY_SIZE>, (int)EInventoryTab::MAX>* arrItem;
	// EInventoryTab eCurrentTab;
	auto [arrItem, eCurrentTab] = Ctx;

	m_eCurrentTab = eCurrentTab;
	m_arrItem = arrItem;
}

void CInventoryUI::OnKeyEventTriggered(TKeyEventCtx Ctx)
{
	auto [eKeyEvent, eKeyState] = Ctx;

	if (eKeyEvent == EEventType::UI_INVENTORY)
	{
		ToggleVisibility();
	}

	if (eKeyEvent == EEventType::)
}
