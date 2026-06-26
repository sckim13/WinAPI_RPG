#pragma once

#include "CComponent.h"

class CTexture;

class CTextureComponent : public CComponent
{
public:
	CTextureComponent();
	virtual ~CTextureComponent();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;
	virtual void Render(HDC hDC, int iOffsetX, int iOffsetY);

	void BindTexture(const wstring& wstrName);

	Vec2 GetTextureSize();

private:
	CTexture* m_pTexture;

public:
};

