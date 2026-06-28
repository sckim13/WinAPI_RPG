#pragma once

#include "CUI.h"

class CTextureComponent;

class CDamageUI : public CUI
{
	CDamageUI();
	virtual ~CDamageUI();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	void AddDamageInfo(const TDamageInfo& tInfo);
	void RenderSingleLine(const TDamageInfo& tInfo);

private:
	list<TDamageInfo> m_listDamage;
	float m_fExpTime = 2.f;

	bool IsExpired(const TDamageInfo& tInfo);
};

