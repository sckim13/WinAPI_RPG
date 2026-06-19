#pragma once

#include "CUI.h"

class CInventory;
struct TInventoryCtx;

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
	void SetInventory(CInventory* pInventory) { m_pInventory = pInventory; }

private:
	CTexture* m_pTexture;
	CInventory* m_pInventory;
};

