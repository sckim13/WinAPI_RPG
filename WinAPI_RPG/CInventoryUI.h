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

private:
	CTexture* m_pMainTexture;
	CCollider* m_pFirstItemCollider; // for testing
	array<array<const CItem*, MAX_INVENTORY_SIZE>, (int)EInventoryTab::MAX> m_arrItem;
	EInventoryTab m_eCurrentTab;

	virtual void OnKeyEventTriggered(TKeyEventCtx Ctx) override;
};

