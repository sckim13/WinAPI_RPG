#pragma once

#include "CComponent.h"
#include "Struct.h"

class CUIComponent : public CComponent
{
public:
	CUIComponent();
	virtual ~CUIComponent();

	virtual void Initialize() PURE;
	virtual void PostInitialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Release() PURE;
	virtual void Render(HDC hDC) PURE;

	virtual void OnPressed();
	virtual void OnDoublePressed();
	virtual void OnHold();
	virtual void OnReleased();
	virtual void OnHoverStarted();
	virtual void OnHoverEnded();
	virtual void OnDragStarted();
	virtual void OnDragEnded();

private:
	TCursorUIInteractionInfo m_tPrevCursorState;
	void CursorUpdate();
};

