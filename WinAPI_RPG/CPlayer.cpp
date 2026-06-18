#include "pch.h"
#include "CPlayer.h"
#include "CKeyManager.h"
#include "CMainGame.h"
#include "CTimeManager.h"
#include "CTexture.h"
#include "CPathManager.h"
#include "CResourceManager.h"
#include "CCollider.h"
#include "CTransform.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{	
	m_pTexture = CResourceManager::GetInstance()->LoadTexture(L"Player", L"Texture\\Player.bmp");
	m_pTexture->SetOwner(this);
	m_pCollider = new CCollider;
	m_pCollider->Initialize();
	m_pCollider->SetOwner(this);
	m_pTransform = new CTransform;
	m_pTransform->SetOwner(this);
}

void CPlayer::PostInitialize()
{
}

void CPlayer::Update()
{
	float fDeltaTime = CTimeManager::GetInstance()->GetDeltaTime();

	Vec2 vPrevPos = GetTransform()->GetPosition();

	if (CKeyManager::GetInstance()->GetKeyState(EKey::LEFT) == EKeyState::HOLD
		&& CKeyManager::GetInstance()->GetKeyState(EKey::RIGHT) == EKeyState::HOLD)
	{

	}
	else if (CKeyManager::GetInstance()->GetKeyState(EKey::LEFT) == EKeyState::HOLD)
	{
		m_ePoseDir = EPoseDirection::LEFT;
		m_ePlayerState = EPlayerState::WALK;
		GetTransform()->SetPosition(vPrevPos + fDeltaTime * Vec2{ -200.f, 0.f });
	}
	else if (CKeyManager::GetInstance()->GetKeyState(EKey::RIGHT) == EKeyState::HOLD)
	{
		m_ePoseDir = EPoseDirection::RIGHT;
		m_ePlayerState = EPlayerState::WALK;
		GetTransform()->SetPosition(vPrevPos + fDeltaTime * Vec2{ 200.f, 0.f });
	}


	if (CKeyManager::GetInstance()->GetKeyState(EKey::UP) == EKeyState::HOLD)
	{
		m_ePlayerState = EPlayerState::WALK;
		GetTransform()->SetPosition(vPrevPos + fDeltaTime * Vec2{ 0.f, -200.f });
	}
	if (CKeyManager::GetInstance()->GetKeyState(EKey::DOWN) == EKeyState::HOLD)
	{
		m_ePlayerState = EPlayerState::WALK;
		GetTransform()->SetPosition(vPrevPos + fDeltaTime * Vec2{ 0.f, 200.f });
	}
	else
	{
		m_ePlayerState = EPlayerState::IDLE;
	}
}

void CPlayer::LateUpdate()
{
	GetCollider()->LateUpdate();
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

	int iWidth = (int)GetTexture()->GetWidth();
	int iHeight = (int)GetTexture()->GetHeight();

	Vec2 vPos = GetTransform()->GetPosition();

	if (m_ePoseDir == EPoseDirection::LEFT)
	{
		StretchBlt(
			hDC,
			(int)(vPos.x - (float)(iWidth / 2)),
			(int)(vPos.y - (float)(iHeight / 2)),
			iWidth, iHeight,
			GetTexture()->GetDC(),
			0, 0, iWidth, iHeight,
			SRCCOPY);
	}
	else
	{
		StretchBlt(
			hDC,
			(int)(vPos.x + (float)(iWidth / 2)),
			(int)(vPos.y - (float)(iHeight / 2)),
			-iWidth, iHeight,
			GetTexture()->GetDC(),
			0, 0, iWidth, iHeight,
			SRCCOPY);
	}


	//TransparentBlt(
	//	hDC,
	//	(int)(vPos.x - (float)(iWidth / 2)),
	//	(int)(vPos.y - (float)(iHeight / 2)),
	//	iWidth, iHeight,
	//	GetTexture()->GetDC(),
	//	0, 0, iWidth, iHeight,
	//	RGB(255, 255, 255)
	//);

	GetCollider()->Render(hDC);
}
