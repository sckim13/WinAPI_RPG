#pragma once

#include "CManager.h"

class CPlayer;

class CItemManager : public CManager
{
	SINGLETON(CItemManager);

public:
	virtual void Initialize() override;
	virtual void PostInitialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
	virtual void Render(HDC hDC) override;

	void RequestEquipItem(EInventoryTab eTab, int iIdx);
	void RequestUnEquipItem(EEquipSlot eSlot);
	void RequestPushItem(CItem* pItem);

private:

public:
};

