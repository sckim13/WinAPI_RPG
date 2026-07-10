#pragma once

#include "CManager.h"

class CCameraManager : public CManager
{
	SINGLETON(CCameraManager);

public:
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	void UpdateScroll(Vec2 vPos);
	inline void SetScrollMode(EScrollMode eMode) { m_eScrollMode = eMode; }
	inline IPoint GetScroll() { return m_ptScroll; }

private:
	void ScrollLock();
	inline void SetScroll(Vec2 vPos) { m_ptScroll = IPoint{ vPos.x, vPos.y }; }
	inline void AddScroll(Vec2 vPos) { m_ptScroll += IPoint{ vPos.x, vPos.y }; }
	
	IPoint m_ptScroll;
	EScrollMode m_eScrollMode;
};

