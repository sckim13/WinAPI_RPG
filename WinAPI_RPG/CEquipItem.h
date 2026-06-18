#pragma once

#include "CItem.h"

class CEquipItem : public CItem
{
public:
	CEquipItem();
	virtual ~CEquipItem();

private:
	EEquipSlot m_eEquipSlot;

public:
	inline EEquipSlot GetEquipSlot() { return m_eEquipSlot; }
};

