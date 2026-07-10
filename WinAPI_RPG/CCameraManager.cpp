#include "pch.h"
#include "CCameraManager.h"
#include "CSceneManager.h"
#include "CScene.h"

CCameraManager::CCameraManager() : m_eScrollMode(EScrollMode::EASE), m_ptScroll{ IPoint{WINCX >> 1, WINCY >> 1} }
{
}

CCameraManager::~CCameraManager()
{
	Release();
}

void CCameraManager::Initialize()
{
}

void CCameraManager::PostInitialize()
{
}

void CCameraManager::Update()
{
}

void CCameraManager::LateUpdate()
{
}

void CCameraManager::Release()
{
}

void CCameraManager::Render(HDC hDC)
{
}

void CCameraManager::ScrollLock()
{
	int iMapWidth = CSceneManager::GetInstance()->GetScene()->GetMapSize().x;
	int iMapHeight = CSceneManager::GetInstance()->GetScene()->GetMapSize().y;

	// 맵이 부자연스러워지는 것을 방지하기 위한 추가 오프셋 (맵의 완전 가장자리를 안보이게끔)
	int iOffset = 10;

	if (m_ptScroll.x > -iOffset) m_ptScroll.x = -iOffset;
	else if (m_ptScroll.x < -(iMapWidth - (WINCX + iOffset))) m_ptScroll.x = -(iMapWidth - (WINCX + iOffset));
	if (m_ptScroll.y > -iOffset) m_ptScroll.y = -iOffset;
	else if (m_ptScroll.y < -(iMapHeight - (WINCY + iOffset))) m_ptScroll.y = -(iMapHeight - (WINCY + iOffset));
}

void CCameraManager::UpdateScroll(Vec2 vPos)
{
	int			iOffsetX = WINCX >> 1;
	int			iOffsetY = WINCY >> 1;

	switch (m_eScrollMode)
	{
	case EScrollMode::NONE:
	{
		break;
	}
	case EScrollMode::LINEAR:
	{
		float fScrollSpeed = 3.f;

		float fDeadZoneX = 50.f;
		if (abs(vPos.x + m_ptScroll.x - iOffsetX) > fDeadZoneX)
		{
			if (iOffsetX > vPos.x + m_ptScroll.x) AddScroll(Vec2{ fScrollSpeed , 0.f });
			if (iOffsetX < vPos.x + m_ptScroll.x) AddScroll(Vec2{ -fScrollSpeed , 0.f });
		}

		float fDeadZoneY = 50.f;
		if (abs(vPos.y + m_ptScroll.y - iOffsetY) > fDeadZoneY)
		{
			if (iOffsetY > vPos.y + m_ptScroll.y) AddScroll(Vec2{ 0.f, fScrollSpeed });
			if (iOffsetY < vPos.y + m_ptScroll.y) AddScroll(Vec2{ 0.f, -fScrollSpeed });
		}

		break;
	}
	case EScrollMode::EASE:
	{
		// how fast chasing the player
		float alpha = 0.05f;

		float fResidualX = vPos.x + m_ptScroll.x - iOffsetX;
		float fScrollXSpeed = alpha * fResidualX;
		AddScroll(Vec2{ -fScrollXSpeed, 0.f });

		float fResidualY = vPos.y + m_ptScroll.y - iOffsetY;
		float fScrollYSpeed = alpha * fResidualY;
		AddScroll(Vec2{ 0.f, -fScrollYSpeed });

		break;
	}
	case EScrollMode::TILE:
	{
		int iIndexX = (vPos.x > 0) ? vPos.x / WINCX : vPos.x / WINCX - 1;
		int iIndexY = (vPos.y > 0) ? vPos.y / WINCY : vPos.y / WINCY - 1;

		SetScroll(Vec2{ -iIndexX * WINCX, -iIndexY * WINCY });

		break;
	}
	default:
		break;
	}

	ScrollLock();
}
