#pragma once
#include "CManager.h"

class CPathManager : public CManager
{
	SINGLETON(CPathManager);

public:
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	inline const wchar_t* GetBasePath() { return m_szBasePath; }

private:
	wchar_t m_szBasePath[MAX_PATH_SIZE];
};

