#pragma once
#include "pch.h"
#include "CObject.h"

class MathUtil
{
public:
	static float Distance(CObject* lhs, CObject* rhs)
	{
		Vec2 dVec = lhs->GetPosition() - rhs->GetPosition();
		return dVec.Size();
	}

	static bool IsPointInRect(IPoint ptPoint, IPoint ptRectPos, IPoint ptRectSize)
	{
		return (ptPoint.x >= ptRectPos.x)
			&& (ptPoint.y >= ptRectPos.y)
			&& (ptPoint.x <= ptRectPos.x + ptRectSize.x)
			&& (ptPoint.y <= ptRectPos.y + ptRectSize.y);
	}
};