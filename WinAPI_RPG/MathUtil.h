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

	static bool IsPointInRect(Vec2 vPoint, Vec2 vRectPos, Vec2 vRectSize)
	{
		return (vPoint.x >= vRectPos.x)
			&& (vPoint.y >= vRectPos.y)
			&& (vPoint.x <= vRectPos.x + vRectSize.x)
			&& (vPoint.y <= vRectPos.y + vRectSize.y);
	}
};