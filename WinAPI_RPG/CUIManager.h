#pragma once

#include "CManager.h"

class CUI;

class CUIManager : public CManager
{
	SINGLETON(CUIManager);

public:
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	CUI* GetUIFromCoordinates(POINT& pt);
	CUI* GetUI(wstring wstrName);

private:
	// All UI Pointers
	map<wstring, CUI*> m_mapUI;
	
	
};

