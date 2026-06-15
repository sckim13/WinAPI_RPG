#pragma once
class CPathManager
{
	SINGLETON(CPathManager);

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Release();

	inline const wchar_t* GetBasePath() { return m_szBasePath; }

private:
	wchar_t m_szBasePath[MAX_PATH_SIZE];
};

