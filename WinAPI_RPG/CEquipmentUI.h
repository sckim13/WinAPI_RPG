#pragma once

#include "CUI.h"

class CTextureComponent;

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

	virtual bool IsValidInput(IPoint ptCursorPos) override;

private:
	CTextureComponent* m_pMainTexture;

	IPoint m_ptDummyItemRect = IPoint{ 100, 100 };

	array<const CItem*, (int)EEquipSlot::MAX> m_arrEquipSlot;

	void OnEquipmentUpdated(const TEquipmentCtx& Ctx);
	virtual void OnKeyEventTriggered(const TKeyEventCtx& Ctx) override;
	virtual void OnMouseEventTriggered(const TMouseEventCtx& Ctx) override;

	// Inherited via CUI
	bool IsCursorOnUI(const IPoint& ptCursorPos) override;
};

