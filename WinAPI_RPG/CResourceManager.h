#pragma once
#include "CManagerBase.h"

class CTexture;

class CResourceManager : public CManagerBase
{
	SINGLETON(CResourceManager)

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	CTexture* LoadTexture(const wstring& strKey, const wstring& strRelPath);

private:
	map<wstring, CTexture*> m_mapTexture;
	CTexture* FindTexture(const wstring& strKey);
};

