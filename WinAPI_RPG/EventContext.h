#pragma once

using namespace std;

#include <array>
#include "Enum.h"
#include "Vec2.h"

class CCollider;
class CItem;
class CObject;

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
};

struct TMouseEventCtx
{
	EKey eKey;
	EKeyState eKeyState;
	Vec2 vCursorPos;
};

struct TCombatCtx
{
	CObject* pSource;
	CObject* pTarget;
	int iDamage;
};