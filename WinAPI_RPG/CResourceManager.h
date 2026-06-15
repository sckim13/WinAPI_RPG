#pragma once

class CTexture;

class CResourceManager
{
	SINGLETON(CResourceManager)

public:
	CTexture* LoadTexture(const wstring& strKey, const wstring& strRelPath);

private:
	map<wstring, CTexture*> m_mapTexture;
	CTexture* FindTexture(const wstring& strKey);
};

