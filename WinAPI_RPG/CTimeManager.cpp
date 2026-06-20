#include "pch.h"
#include "CTimeManager.h"
#include "CMainGame.h"

CTimeManager::CTimeManager()
	: m_llGlobalCount{}, m_llCurrentCount {}, m_llFrequency{}, m_llPreviousCount{}, m_dDeltaTime(0),
	m_dAccumulatedTime(0), m_iCountPerSecond(0), m_iTargetFPS(60.f), m_iActualFPS(0)
{

}

CTimeManager::~CTimeManager()
{

}

void CTimeManager::Initialize()
{
	QueryPerformanceCounter(&m_llCurrentCount);
	QueryPerformanceCounter(&m_llPreviousCount);
	QueryPerformanceCounter(&m_llGlobalCount);
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeManager::PostInitialize()
{
}

void CTimeManager::Update()
{
	
	while (m_dAccumulatedTime < 1.f / (float)m_iTargetFPS)
	{
		QueryPerformanceCounter(&m_llCurrentCount);
		m_dAccumulatedTime = (double)(m_llCurrentCount.QuadPart - m_llPreviousCount.QuadPart) / (double)m_llFrequency.QuadPart;
	}

	m_dDeltaTime = m_dAccumulatedTime;
	m_iActualFPS = 1.f / m_dDeltaTime;
	wchar_t szBuffer[255] = {};
	swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iActualFPS, m_dDeltaTime);
	SetWindowText(CMainGame::GetInstance()->GetHWnd(), szBuffer);

	m_dAccumulatedTime = 0;
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