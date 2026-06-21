#pragma once

#include "CUI.h"

class CTexture;

class CInventoryUI : public CUI
{
public:
	CInventoryUI();
	virtual ~CInventoryUI();

	void Initialize() override;
	void PostInitialize() override;
	void Update() override;
	void LateUpdate() override;
	void Release() override;
	void Render(HDC hDC) override;

	void OnInventoryUpdated(TInventoryCtx Ctx);

	virtual bool IsValidInput(Vec2 vCursorPos) override;

private:
	CTexture* m_pMainTexture;
	Vec2 m_pDummyItemRect = Vec2 {100.f, 100.f};
	array<array<const CItem*, MAX_INVENTORY_SIZE>, (int)EInventoryTab::MAX> m_arrItem;
	EInventoryTab m_eCurrentTab;

	virtual void OnKeyEventTriggered(TKeyEventCtx Ctx) override;
	virtual void OnMouseEventTriggered(TMouseEventCtx Ctx) override;

	// Inherited via CUI
	bool IsCursorOnUI(Vec2 vCursorPos) override;
};

