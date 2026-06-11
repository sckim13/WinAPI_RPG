#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeManager.h"
#include "CKeyManager.h"

CCore* CCore::g_pInst = nullptr;

CCore::CCore()
	: m_hWnd(nullptr), m_WndResolution{}, m_hDC(nullptr),
	m_hBitmap(nullptr), m_hDCMem(nullptr)
{
}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_hDCMem);
	DeleteObject(m_hBitmap);
}

CObject g_obj;

HRESULT CCore::Initialize(HWND hWnd, POINT WndResolution)
{
	// handle initialize
	m_hWnd = hWnd;
	m_WndResolution = WndResolution;

	// set window size
	RECT rect = { 0, 0, WndResolution.x, WndResolution.y };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, true); 

	int iScreenW = GetSystemMetrics(SM_CXSCREEN);
	int iScreenH = GetSystemMetrics(SM_CYSCREEN);

	int iWindowW = rect.right - rect.left;
	int iWindowH = rect.bottom - rect.top;

	SetWindowPos(m_hWnd, nullptr, (iScreenW - iWindowW) / 2, (iScreenH - iWindowH) / 2, iWindowW, iWindowH, 0);

	// Manager initialize
	CTimeManager::GetInstance()->Initialize();
	CKeyManager::GetInstance()->Initialize();

	// get device context
	m_hDC = GetDC(m_hWnd);

	// create back buffer
	m_hBitmap = CreateCompatibleBitmap(m_hDC, m_WndResolution.x, m_WndResolution.y);
	m_hDCMem = CreateCompatibleDC(m_hDC);
	SelectObject(m_hDCMem, m_hBitmap);

	// object handling
	g_obj.SetPosition(Vec2{ m_WndResolution.x / 2, m_WndResolution.y / 2 });
	g_obj.SetScale(Vec2{ 100, 100 });

	return S_OK;
}

void CCore::Update()
{
	// update other managers
	// get deltatime
	CTimeManager::GetInstance()->Update();
	// float fDeltaTime = CTimeManager::GetInstance()->GetDeltaTime();
	float fDeltaTime = 1;

	CKeyManager::GetInstance()->Update();

	if (CKeyManager::GetInstance()->GetKeyState(EKey::LEFT) == EKeyState::PRESSED)
	{
		g_obj.SetPosition(g_obj.GetPosition() + fDeltaTime * Vec2{-100.f, 0.f});
	}
	if (CKeyManager::GetInstance()->GetKeyState(EKey::RIGHT) == EKeyState::PRESSED)
	{
		g_obj.SetPosition(g_obj.GetPosition() + fDeltaTime * Vec2{100.f, 0.f});
	}
	if (CKeyManager::GetInstance()->GetKeyState(EKey::UP) == EKeyState::PRESSED)
	{
		g_obj.SetPosition(g_obj.GetPosition() + fDeltaTime * Vec2{0.f, -100.f});
	}
	if (CKeyManager::GetInstance()->GetKeyState(EKey::DOWN) == EKeyState::PRESSED)
	{
		g_obj.SetPosition(g_obj.GetPosition() + fDeltaTime * Vec2{0.f, 100.f});
	}
}

void CCore::Render()
{
	Rectangle(m_hDCMem, -1, -1, m_WndResolution.x + 1, m_WndResolution.y + 1);
	
	Rectangle(
		m_hDCMem,
		(int)g_obj.GetPosition().x - (int)g_obj.GetScale().x / 2,
		(int)g_obj.GetPosition().y - (int)g_obj.GetScale().y / 2,
		(int)g_obj.GetPosition().x + (int)g_obj.GetScale().x / 2,
		(int)g_obj.GetPosition().y + (int)g_obj.GetScale().y / 2
	);

	BitBlt(m_hDC, 0, 0, m_WndResolution.x, m_WndResolution.y,
		m_hDCMem, 0, 0, SRCCOPY);

	//Rectangle(m_hDC, -1, -1, m_WndResolution.x + 1, m_WndResolution.y + 1);

	//Rectangle(
	//	m_hDC,
	//	(int)g_obj.GetPosition().x - (int)g_obj.GetScale().x / 2,
	//	(int)g_obj.GetPosition().y - (int)g_obj.GetScale().y / 2,
	//	(int)g_obj.GetPosition().x + (int)g_obj.GetScale().x / 2,
	//	(int)g_obj.GetPosition().y + (int)g_obj.GetScale().y / 2
	//);
}
