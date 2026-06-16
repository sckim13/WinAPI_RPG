#pragma once
#include "CManagerBase.h"

class CPathManager : public CManagerBase
{
	SINGLETON(CPathManager);

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Release() override;

	inline const wchar_t* GetBasePath() { return m_szBasePath; }

private:
	wchar_t m_szBasePath[MAX_PATH_SIZE];
};

