#pragma once

#include "CManager.h"

class CTimerManager : public CManager
{
	SINGLETON(CTimerManager);

public:
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	void SetTimer(TTimerHandle& THandle, function<void()> F, float fDelay, bool bLoop, float fFirstDelay = -1.f);
	void RestartTimer(TTimerHandle& THandle);
	void ClearTimer(TTimerHandle& THandle);
	void DeleteHandle(INT64 h_ID);


private:
	static INT64 g_ID;
	map<INT64, TTimerCtx*> m_mapCtx;

};