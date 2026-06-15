#pragma once
class CResource
{
public:
	CResource();
	virtual ~CResource();

	virtual void Initialize();
	virtual void Update();
	virtual void Release();

	virtual void Render();

	inline void SetKey(const wstring& strKey) { m_strKey = strKey; }
	inline void SetRelativePath(const wstring& strRelPath) { m_strRelPath = strRelPath; }
	
	inline wstring& GetKey() { return m_strKey; }
	inline wstring& GetRelativePath() { return m_strRelPath; }

private:
	wstring m_strKey;
	wstring m_strRelPath;
};

