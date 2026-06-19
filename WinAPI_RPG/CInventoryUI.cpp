#include "pch.h"
#include "CInventoryUI.h"
#include "CInventory.h"
#include "CEventHandle.h"
#include "EventContext.h"
#include "CResourceManager.h"
#include "CTexture.h"
#include "CSceneManager.h"
#include "CPlayer.h"

CInventoryUI::CInventoryUI()
{
}

CInventoryUI::~CInventoryUI()
{
}

void CInventoryUI::Initialize()
{
	m_pTexture = CResourceManager::GetInstance()->LoadTexture(L"Inventory", L"Texture\\Inventory.bmp");
	m_pInventory = CSceneManager::GetInstance()->GetPlayer()->GetInventory();
	m_pInventory->m_hOnInventoryUpdated->AddBinding(this, [this](TInventoryCtx Ctx) { OnInventoryUpdated(Ctx); });
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

	int iWidth = (int)m_pTexture->GetWidth();
	int iHeight = (int)m_pTexture->GetHeight();

	Vec2 vPos = GetTransform()->GetPosition();


	TransparentBlt(
		hDC,
		(int)(vPos.x - (float)(iWidth / 2)),
		(int)(vPos.y - (float)(iHeight / 2)),
		iWidth, iHeight,
		m_pTexture->GetDC(),
		0, 0, iWidth, iHeight,
		RGB(255, 255, 255)
	);
}

void CInventoryUI::OnInventoryUpdated(TInventoryCtx Ctx)
{
	cout << "인벤토리 업데이트" << endl;
}
