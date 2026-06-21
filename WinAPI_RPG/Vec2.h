#pragma once

class Vec2
{
public:
	Vec2() : x(0.f), y(0.f) {}

	template<typename T>
	Vec2(T _x, T _y) : x((float)_x), y((float)_y) {}

	Vec2 operator+(const Vec2& other) const
	{
		return Vec2{ x + other.x, y + other.y };
	}

	Vec2 operator-(const Vec2& other) const
	{
		return Vec2{ x - other.x, y - other.y };
	}

	Vec2& operator+=(const Vec2& other)
	{
		x += other.x; y += other.y;
		return *this;
	}

	Vec2& operator-=(const Vec2& other)
	{
		x -= other.x; y -= other.y;
		return *this;
	}

	template<typename T>
	Vec2 operator*(const T& other)
	{
		return Vec2{ x * other, y * other };
	}

	inline float Size() const { return sqrt(x * x + y * y); }

public:
	float x;
	float y;

};

template<typename T>
inline Vec2 operator*(const T& lhs, const Vec2& rhs)
{
	return Vec2{ lhs * rhs.x, lhs * rhs.y };
}

inline std::ostream& operator<<(std::ostream& os, const Vec2& rhs)
{
	os << "(" << rhs.x << ", " << rhs.y << ")";
	return os;
}