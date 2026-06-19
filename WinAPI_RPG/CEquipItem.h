#pragma once

#include "CItem.h"

class CEquipItem : public CItem
{
public:
	CEquipItem();
	virtual ~CEquipItem();

	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

private:
	EEquipSlot m_eEquipSlot;

public:
	inline EEquipSlot GetEquipSlot() { return m_eEquipSlot; }

	// Inherited via CItem
};

