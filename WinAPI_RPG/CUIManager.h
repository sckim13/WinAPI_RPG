#pragma once

#include "CManager.h"

class CUI;
class CCursor;

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

	CUI* GetUI(wstring wstrName);

	void OnMouseEventTriggered(const TMouseEventCtx& Ctx);

	void UpdateUIOrder(CUI* pUI);

private:
	// Separate DamageUI since it does not have order
	CUI* m_pDamageUI;
	
	// All UI Pointers
	map<wstring, CUI*> m_mapUI;


	list<CUI*> m_listUI;
	unordered_map<CUI*, list<CUI*>::iterator> m_umapUI;

	CCursor* m_pCursor;
	
};

