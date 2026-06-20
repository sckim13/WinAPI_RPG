#include "pch.h"
#include "CCursor.h"
#include "CTexture.h"
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

	m_pTexture = CResourceManager::GetInstance()->LoadTexture(L"Cursor", L"Texture\\Cursor.bmp");

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
	GetTexture()->Render(hDC, (int)GetPosition().x, (int)GetPosition().y);
}
