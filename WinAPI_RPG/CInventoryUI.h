#pragma once

#include "CUI.h"

class CTexture;

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

	void OnInventoryUpdated(TInventoryCtx Ctx);

	virtual bool IsValidInput(Vec2 vCursorPos) override;

	virtual void OnKeyEventTriggered(TKeyEventCtx Ctx) override;
	virtual void OnMouseEventTriggered(TMouseEventCtx Ctx) override;
private:
	CTexture* m_pMainTexture;
	Vec2 m_pDummyItemRect = Vec2 {100.f, 100.f};
	array<array<const CItem*, MAX_INVENTORY_SIZE>, (int)EInventoryTab::MAX> m_arrItem;
	EInventoryTab m_eCurrentTab;


	// Inherited via CUI
	bool IsCursorOnUI(Vec2 vCursorPos) override;
};

