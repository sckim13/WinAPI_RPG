#pragma once
#include "CManager.h"

class CTimeManager : public CManager
{
	SINGLETON(CTimeManager);

public:
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;


	inline float GetDeltaTime() { return static_cast<float>(m_dDeltaTime); }
	inline float GetTime() { return static_cast<float>((double)(m_llCurrentCount.QuadPart - m_llGlobalCount.QuadPart) / (double)m_llFrequency.QuadPart); }

private:
	LARGE_INTEGER m_llGlobalCount;
	LARGE_INTEGER m_llCurrentCount;
	LARGE_INTEGER m_llFrequency;
	LARGE_INTEGER m_llPreviousCount;

	double m_dDeltaTime;
	double m_dAccumulatedTime;
	UINT m_iCountPerSecond;
	UINT m_iFPS;
};

