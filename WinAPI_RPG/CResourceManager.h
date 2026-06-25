#pragma once
#include "CManager.h"

class CTexture;

class CResourceManager : public CManager
{
	SINGLETON(CResourceManager)

public:
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;
public:
	CTexture* LoadTexture(const wstring& strKey, const wstring& strRelPath);

private:
	map<wstring, CTexture*> m_mapTexture;
	CTexture* FindTexture(const wstring& strKey);
};

