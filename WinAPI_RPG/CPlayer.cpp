#include "pch.h"
#include "CPlayer.h"
#include "CKeyManager.h"
#include "CMainGame.h"
#include "CTimeManager.h"
#include "CTexture.h"
#include "CPathManager.h"
#include "CResourceManager.h"

CPlayer::CPlayer()
{
	Initialize();
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initialize()
{	
	m_pTexture = CResourceManager::GetInstance()->LoadTexture(L"Player", L"Texture\\Player.bmp");
}

void CPlayer::Update()
{
	float fDeltaTime = CTimeManager::GetInstance()->GetDeltaTime();
	if (CKeyManager::GetInstance()->GetKeyState(EKey::LEFT) == EKeyState::HOLD)
	{
		SetPosition(GetPosition() + fDeltaTime * Vec2{ -100.f, 0.f });
	}
	if (CKeyManager::GetInstance()->GetKeyState(EKey::RIGHT) == EKeyState::HOLD)
	{
		SetPosition(GetPosition() + fDeltaTime * Vec2{ 100.f, 0.f });
	}
	if (CKeyManager::GetInstance()->GetKeyState(EKey::UP) == EKeyState::HOLD)
	{
		SetPosition(GetPosition() + fDeltaTime * Vec2{ 0.f, -100.f });
	}
	if (CKeyManager::GetInstance()->GetKeyState(EKey::DOWN) == EKeyState::HOLD)
	{
		SetPosition(GetPosition() + fDeltaTime * Vec2{ 0.f, 100.f });
	}
}

void CPlayer::Release()
{
}

void CPlayer::Render(HDC hDC)
{
	/*
	Rectangle(
		hDC,
		(int)GetPosition().x - (int)(GetScale().x / 2),
		(int)GetPosition().y - (int)(GetScale().y / 2),
		(int)GetPosition().x + (int)(GetScale().x / 2),
		(int)GetPosition().y + (int)(GetScale().y / 2)
	);
	BitBlt(
		CMainGame::GetInstance()->GetMemDC(),
		(int)(vPos.x - (float)(iWidth / 2)),
		(int)(vPos.y - (float)(iHeight / 2)),
		iWidth, iHeight,
		m_pTexture->GetDC(),
		0, 0, SRCCOPY
	);
	*/

	int iWidth = (int)m_pTexture->GetWidth();
	int iHeight = (int)m_pTexture->GetHeight();

	Vec2 vPos = GetPosition();


	TransparentBlt(
		hDC,
		(int)(vPos.x - (float)(iWidth / 2)),
		(int)(vPos.y - (float)(iHeight / 2)),
		iWidth, iHeight,
		m_pTexture->GetDC(),
		0, 0, iWidth, iHeight,
		RGB(81, 110, 155)
	);
}
