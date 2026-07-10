#pragma once

class Vec2;

class IPoint
{
public:
	IPoint() : x(0), y(0) {}
	explicit IPoint(const Vec2& v);

	template<typename T>
	IPoint(T _x, T _y) : x((int)_x), y((int)_y) {}

	IPoint operator+(const IPoint& other) const
	{
		return IPoint{ x + other.x, y + other.y };
	}

	IPoint operator-(const IPoint& other) const
	{
		return IPoint{ x - other.x, y - other.y };
	}

	IPoint& operator+=(const IPoint& other)
	{
		x += other.x; y += other.y;
		return *this;
	}

	IPoint& operator-=(const IPoint& other)
	{
		x -= other.x; y -= other.y;
		return *this;
	}

public:
	int x;
	int y;

};

inline std::ostream& operator<<(std::ostream& os, const IPoint& rhs)
{
	os << "(" << rhs.x << ", " << rhs.y << ")";
	return os;
}