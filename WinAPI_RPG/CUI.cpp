#include "pch.h"
#include "CUI.h"
#include "CKeyManager.h"

CUI::CUI() : m_bVisible(false)
{
}

CUI::~CUI()
{
}

void CUI::Initialize()
{
	CKeyManager::GetInstance()->m_hOnKeyEventTriggered->AddBinding(
		this,
		[this](TKeyEventCtx Ctx) { OnKeyEventTriggered(Ctx); });
}

void CUI::PostInitialize()
{
}

void CUI::Update()
{
}

void CUI::LateUpdate()
{
}

void CUI::Release()
{
}

void CUI::Render(HDC hDC)
{
}

void CUI::OnKeyEventTriggered(TKeyEventCtx Ctx)
{
}
