#include "pch.h"
#include "CTimerManager.h"
#include "CTimeManager.h"

INT64 CTimerManager::g_ID = 0;

CTimerManager::CTimerManager()
{
}

CTimerManager::~CTimerManager()
{
}

void CTimerManager::Initialize()
{
}

void CTimerManager::PostInitialize()
{
}

void CTimerManager::Update()
{
	queue<INT64> EraseQueue;
	float fTime = CTimeManager::GetInstance()->GetTime();
	for (auto iter = m_mapCtx.begin(); iter != m_mapCtx.end(); ++iter)
	{
		INT64 h_ID = iter->first;
		TTimerCtx* TCtx = iter->second;
		if (TCtx->OnTime(fTime))
		{
			// cout << "[Handle No. " << h_ID << "] ";
			// cout << "Timer Function Execute : Current Time(ms) " << dwTime << ", Last Executed Time(ms) " << TCtx->GetPrevExecutedTime();
			//cout << setprecision(7);
			//cout << ", DT(s) " << (fTime - TCtx->GetPrevExecutedTime()) << endl;
			TCtx->Execute();
			TCtx->SetPrevExecutedTime(fTime);
			if (TCtx->IsLoop() == false)
			{
				cout << "[Handle No. " << h_ID << "] ";
				cout << "루프 함수가 아니므로 제거합니다" << endl;
				EraseQueue.push(h_ID);
			}
		}
	}
	while (!EraseQueue.empty())
	{
		DeleteHandle(EraseQueue.front());
		EraseQueue.pop();
	}
}

void CTimerManager::LateUpdate()
{
}

void CTimerManager::Release()
{
}

void CTimerManager::Render(HDC hDC)
{
}

void CTimerManager::SetTimer(TTimerHandle& THandle, function<void()> F, float fDuration, bool bLoop, float fFirstDelay)
{
	float fTime = CTimeManager::GetInstance()->GetTime();

	if (THandle.m_ID == -1)
	{
		/* SetTimer had been executed by the same Handle before */
		THandle.m_ID = ++g_ID;
	}
	TTimerCtx* TCtx = new TTimerCtx;
	TCtx->SetDuration(fDuration);
	TCtx->SetLoop(bLoop);
	TCtx->SetF(F);
	cout << "[Handle No. " << THandle.m_ID << "] ";
	cout << "핸들 등록 시간 : Current Time(ms) " << fTime << endl;
	if (fFirstDelay < 0.f)
	{
		cout << "[Handle No. " << THandle.m_ID << "] ";
		cout << fDuration << "초 후 실행합니다" << endl;
		TCtx->SetPrevExecutedTime(fTime);
	}
	else
	{
		cout << "[Handle No. " << THandle.m_ID << "] ";
		cout << fFirstDelay << "초 후 실행합니다" << endl;
		TCtx->SetPrevExecutedTime(fTime + (fFirstDelay - fDuration));
	}
	m_mapCtx.insert_or_assign(THandle.m_ID, TCtx);
}

void CTimerManager::RestartTimer(TTimerHandle& THandle)
{
	float fTime = CTimeManager::GetInstance()->GetTime();

	INT64 h_ID = THandle.m_ID;
	if (m_mapCtx.find(h_ID) == m_mapCtx.end()) return;
	m_mapCtx[h_ID]->SetPrevExecutedTime(fTime);
}

void CTimerManager::ClearTimer(TTimerHandle& THandle)
{
	DeleteHandle(THandle.m_ID);
}

void CTimerManager::DeleteHandle(INT64 h_ID)
{
	cout << "Delete Handle No. " << h_ID << endl;
	if (m_mapCtx.find(h_ID) == m_mapCtx.end()) return;
	delete m_mapCtx.at(h_ID);
	m_mapCtx.erase(h_ID);
}
