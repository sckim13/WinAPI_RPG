#pragma once

#include "CBase.h"

class CUI : public CBase
{
public:
	CUI();
	virtual ~CUI();

	virtual void Initialize() PURE;
	virtual void PostInitialize() PURE;
	virtual void Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Release() PURE;
	virtual void Render(HDC hDC) PURE;

private:
	bool m_bVisible;

public:
	bool IsVisible() { return m_bVisible; }
	void SetVisibility(bool bVisible) { m_bVisible = bVisible; }
	void ToggleVisibility() { m_bVisible = !m_bVisible; }
};

