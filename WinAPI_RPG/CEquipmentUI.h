#pragma once

#include "CUI.h"

class CTexture;

class CEquipmentUI : public CUI
{
public:
	CEquipmentUI();
	virtual ~CEquipmentUI();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	virtual bool IsValidInput(Vec2 vCursorPos) override;

private:
	CTexture* m_pMainTexture;

	Vec2 m_pDummyItemRect = Vec2{ 100.f, 100.f };

	array<const CItem*, (int)EEquipSlot::MAX> m_arrEquipSlot;

	void OnEquipmentUpdated(TEquipmentCtx Ctx);
	virtual void OnKeyEventTriggered(TKeyEventCtx Ctx) override;
	virtual void OnMouseEventTriggered(TMouseEventCtx Ctx) override;

	// Inherited via CUI
	bool IsCursorOnUI(Vec2 vCursorPos) override;
};

