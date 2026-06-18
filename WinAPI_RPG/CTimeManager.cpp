#include "pch.h"
#include "CTimeManager.h"
#include "CMainGame.h"

CTimeManager::CTimeManager()
	: m_llGlobalCount{}, m_llCurrentCount {}, m_llFrequency{}, m_llPreviousCount{}, m_dDeltaTime(0),
	m_dAccumulatedTime(0), m_iCountPerSecond(0), m_iFPS(0)
{

}

CTimeManager::~CTimeManager()
{

}

void CTimeManager::Initialize()
{
	QueryPerformanceCounter(&m_llCurrentCount);
	QueryPerformanceCounter(&m_llGlobalCount);
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeManager::PostInitialize()
{
}

void CTimeManager::Update()
{
	QueryPerformanceCounter(&m_llCurrentCount);

	m_dDeltaTime = (double)(m_llCurrentCount.QuadPart - m_llPreviousCount.QuadPart) / (double)m_llFrequency.QuadPart;
	m_dAccumulatedTime += m_dDeltaTime;
	++m_iCountPerSecond;

	if (m_dAccumulatedTime >= 1.0)
	{
		m_iFPS = m_iCountPerSecond;
		m_dAccumulatedTime = 0;
		m_iCountPerSecond = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDeltaTime);
		SetWindowText(CMainGame::GetInstance()->GetHWnd(), szBuffer);
	}
	m_llPreviousCount = m_llCurrentCount;
}

void CTimeManager::LateUpdate()
{
}

void CTimeManager::Release()
{
}

void CTimeManager::Render(HDC hDC)
{
}