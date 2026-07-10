#pragma once

#include "CUI.h"

class CTexture;
class CTextureComponent;

class CInventoryUI : public CUI
{
public:
	CInventoryUI();
	virtual ~CInventoryUI();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	void OnInventoryUpdated(const TInventoryCtx& Ctx);

	virtual bool IsValidInput(IPoint ptCursorPos) override;

	virtual void OnKeyEventTriggered(const TKeyEventCtx& Ctx) override;
	virtual void OnMouseEventTriggered(const TMouseEventCtx& Ctx) override;
private:
	CTextureComponent* m_pMainTexture;
	IPoint m_ptDummyItemRect = IPoint {100, 100};
	array<array<const CItem*, MAX_INVENTORY_SIZE>, (int)EInventoryTab::MAX> m_arrItem;
	EInventoryTab m_eCurrentTab;


	// Inherited via CUI
	bool IsCursorOnUI(const IPoint& ptCursorPos) override;
};

