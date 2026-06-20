#include "pch.h"
#include "CEquipmentUI.h"
#include "CSceneManager.h"
#include "CPlayer.h"
#include "CEquipment.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CItem.h"

CEquipmentUI::CEquipmentUI() : m_pMainTexture(nullptr)
{
}

CEquipmentUI::~CEquipmentUI()
{
}

void CEquipmentUI::Initialize()
{
	__super::Initialize();

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
			pItem->GetTexture()->Render(hDC, (int)GetPosition().x + 100, (int)GetPosition().y + 100);
		}
	}
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
	}
}
