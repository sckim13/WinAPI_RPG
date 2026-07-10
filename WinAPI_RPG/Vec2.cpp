#include "pch.h"
#include "Vec2.h"

Vec2::Vec2(const IPoint& pt) : x(static_cast<float>(pt.x)), y(static_cast<float>(pt.y))
{
}
