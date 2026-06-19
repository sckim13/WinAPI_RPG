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
};