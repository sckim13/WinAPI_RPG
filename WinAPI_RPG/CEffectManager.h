#pragma once

#include "CManager.h"

class CTexture;

class CEffectManager : public CManager
{
	SINGLETON(CEffectManager);

public:
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	void SwtichDamageSkin();

	void AddDamageInfo(const TDamageInfo & tInfo);

private:
	CTexture* m_vecDamageTexture[10];

	list<TDamageInfo> m_listDamage;
	float m_fExpTime = 2.f;

	void RenderSingleDamage(HDC hDC, const TDamageInfo & tInfo) const;
	bool IsExpired(const TDamageInfo& tInfo);
};

