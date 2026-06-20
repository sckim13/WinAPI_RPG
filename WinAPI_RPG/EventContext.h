#pragma once

using namespace std;

#include <array>
#include "Enum.h"

class CCollider;
class CItem;

struct TCollisionCtx
{
	CCollider* pCounterPart;
};

struct TInventoryCtx
{
	array<array<const CItem*, MAX_INVENTORY_SIZE>, (int)EInventoryTab::MAX> arrItem;
	EInventoryTab eCurrentTab;
};

struct TEquipmentCtx
{
	array<const CItem*, (int)EEquipSlot::MAX> arrEquipSlot;
};

struct TKeyEventCtx
{
	EEventType eEventType;
	EKeyState eKeyState;
	POINT ptMousePos;
};