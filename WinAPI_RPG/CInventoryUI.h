#pragma once

#include "CUI.h"

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

private:
};

