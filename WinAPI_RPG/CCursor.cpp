#include "pch.h"
#include "CCursor.h"
#include "CTextureComponent.h"
#include "CResourceManager.h"
#include "CMainGame.h"

CCursor::CCursor() : m_ptCursorPos{}, m_eCursorState(ECursorState::IDLE)
{
}

CCursor::~CCursor()
{
}

void CCursor::Initialize()
{
	m_pTextureComponent = new CTextureComponent;
	m_pTextureComponent->AttachTo(this);
	m_pTextureComponent->BindTexture(L"Cursor");
	m_pTextureComponent->SetScrollEnabled(false);

	// TODO mouse animator
	
	__super::Initialize();
}

void CCursor::PostInitialize()
{
}

void CCursor::Update()
{
	POINT pt{};
	GetCursorPos(&pt);
	ScreenToClient(CMainGame::GetInstance()->GetHWnd(), &pt);
	m_ptCursorPos = IPoint{pt.x, pt.y};
	SetPosition(Vec2{m_ptCursorPos.x, m_ptCursorPos.y});
}

void CCursor::LateUpdate()
{
}

void CCursor::Release()
{
}

void CCursor::Render(HDC hDC)
{
	GetTextureComponent()->Render(hDC);
}
