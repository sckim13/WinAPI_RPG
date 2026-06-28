#pragma once

#include "CObject.h"

class CUI : public CObject
{
public:
	CUI();
	virtual ~CUI();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	virtual bool IsCursorOnUI(Vec2 vCursorPos);
	virtual bool IsValidInput(Vec2 vCursorPos);

	void MoveUI(EKeyState eKeyState, const Vec2& vCursorPos);
	virtual void OnMouseEventTriggered(const TMouseEventCtx& Ctx);

protected:
	virtual void OnKeyEventTriggered(const TKeyEventCtx& Ctx);

	void OnFocused();

private:
	bool m_bVisible;

	EUIType m_eUIType;
	EUIStatus m_eUIStatus;

	// Caching position for UI Drag
	Vec2 m_vDragCursorOrigin;
	Vec2 m_vDragUIOrigin;
	void SetDragOrigin(Vec2 vUIPos, Vec2 vCursorPos);

	/* TODO : Later get real value from asset */
	Vec2 m_vDummyDragArea = Vec2 {100.f, 100.f};

public:
	bool IsVisible() { return m_bVisible; }
	void ToggleVisibility() { m_bVisible = !m_bVisible; }
	
	void SetUIType(EUIType eUItype) { m_eUIType = eUItype; }
	void SetVisibility(bool bVisible) { m_bVisible = bVisible; }
	void SetUIStatus(EUIStatus eUIStatus) { m_eUIStatus = eUIStatus; }
	
	EUIType GetUIType() { return m_eUIType; }
	EUIStatus GetUIStatus() { return m_eUIStatus; }
};

