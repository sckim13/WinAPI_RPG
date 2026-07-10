#include "pch.h"
#include "IPoint.h"

IPoint::IPoint(const Vec2& v) : x(static_cast<int>(v.x)), y(static_cast<int>(v.y))
{
}
