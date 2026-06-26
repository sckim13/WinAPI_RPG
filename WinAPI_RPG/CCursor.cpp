#include "pch.h"
#include "CCursor.h"
#include "CTextureComponent.h"
#include "CResourceManager.h"
#include "CMainGame.h"

CCursor::CCursor() : m_ptCursorPos{}
{
}

CCursor::~CCursor()
{
}

void CCursor::Initialize()
{
	__super::Initialize();

	m_pTextureComponent = new CTextureComponent;
	m_pTextureComponent->SetOwner(this);
	m_pTextureComponent->BindTexture(L"Cursor");
}

void CCursor::PostInitialize()
{
}

void CCursor::Update()
{
	GetCursorPos(&m_ptCursorPos);
	ScreenToClient(CMainGame::GetInstance()->GetHWnd(), &m_ptCursorPos);
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
