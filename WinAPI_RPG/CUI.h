#pragma once

#include "CBase.h"

class CUI : public CBase
{
public:
	CUI();
	virtual ~CUI();

	virtual void Initialize() override;
	virtual void PostInitialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Release() PURE;
	virtual void Render(HDC hDC);

	virtual bool IsCursorOnUI(Vec2 vCursorPos);
	virtual bool IsValidInput(Vec2 vCursorPos);

	void MoveUI(EKeyState eKeyState, const Vec2& vCursorPos);
	virtual void OnMouseEventTriggered(TMouseEventCtx Ctx);

protected:
	virtual void OnKeyEventTriggered(TKeyEventCtx Ctx);

	void OnFocused();

private:
	bool m_bVisible;

	EUIType m_eUIType;
	EUIStatus m_eUIStatus;

	Vec2 m_vCursorPosCached;

	/* TODO : Later get real value from asset */
	Vec2 m_vDummyDragArea = Vec2 {100.f, 100.f};

public:
	bool IsVisible() { return m_bVisible; }
	void ToggleVisibility() { m_bVisible = !m_bVisible; }
	
	void SetUIType(EUIType eUItype) { m_eUIType = eUItype; }
	void SetVisibility(bool bVisible) { m_bVisible = bVisible; }
	void SetCursorPressedPoint(Vec2 vCursorPos) { m_vCursorPosCached = vCursorPos; }
	void SetUIStatus(EUIStatus eUIStatus) { m_eUIStatus = eUIStatus; }
	
	EUIType GetUIType() { return m_eUIType; }
	EUIStatus GetUIStatus() { return m_eUIStatus; }
};

