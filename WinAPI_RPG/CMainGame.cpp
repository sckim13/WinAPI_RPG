#include "pch.h"
#include "CMainGame.h"

#include "CTimeManager.h"
#include "CKeyManager.h"
#include "CSceneManager.h"
#include "CPathManager.h"

CMainGame::CMainGame()
	: m_hWnd(nullptr), m_WndResolution{}, m_hDC(nullptr),
	m_hBitmap(nullptr), m_hDCMem(nullptr)
{
}

CMainGame::~CMainGame()
{
	ReleaseDC(m_hWnd, m_hDC);

	DeleteDC(m_hDCMem);
	DeleteObject(m_hBitmap);
}

void CMainGame::Initialize()
{
	// Do Not Use
}

HRESULT CMainGame::Initialize(HWND hWnd, POINT WndResolution)
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
	CSceneManager::GetInstance()->Initialize();
	CPathManager::GetInstance()->Initialize();

	// get device context
	m_hDC = GetDC(m_hWnd);

	// create back buffer
	m_hBitmap = CreateCompatibleBitmap(m_hDC, m_WndResolution.x, m_WndResolution.y);
	m_hDCMem = CreateCompatibleDC(m_hDC);
	SelectObject(m_hDCMem, m_hBitmap);

	return S_OK;
}


void CMainGame::PostInitialize()
{
}


void CMainGame::Update()
{
	// update other managers
	// get deltatime
	CTimeManager::GetInstance()->Update();
	CKeyManager::GetInstance()->Update();
	CSceneManager::GetInstance()->Update();

	if(CKeyManager::GetInstance()->GetKeyState(EKey::ESCAPE) == EKeyState::PRESSED)
	{
		DestroyWindow(m_hWnd);
		return;
	}
}

void CMainGame::LateUpdate()
{
	CSceneManager::GetInstance()->LateUpdate();
}

void CMainGame::Release()
{
}

void CMainGame::Render(HDC hDC)
{
	// Do Not Use
}

void CMainGame::Render()
{
	Rectangle(m_hDCMem, -1, -1, m_WndResolution.x + 1, m_WndResolution.y + 1);

	CSceneManager::GetInstance()->Render(m_hDCMem);

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
