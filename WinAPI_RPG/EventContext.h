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
	array<array<CItem*, MAX_INVENTORY_SIZE>, (int)EInventoryTab::MAX>* pItemContainer;
	EInventoryTab eCurrentTab;
};