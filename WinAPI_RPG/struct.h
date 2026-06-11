#pragma once

struct Vec2
{
public:
	Vec2() : x(0.f), y(0.f) {}
	Vec2(float _x, float _y) : x(_x), y(_y) {}
	Vec2(int _x, int _y) : x((float)_x), y((float)_y) {}
	Vec2(long _x, long _y) : x((float)_x), y((float)_y) {}

	Vec2 operator+(const Vec2& other)
	{
		return Vec2{ x + other.x, y + other.y };
	}

	Vec2 operator-(const Vec2& other)
	{
		return Vec2{ x - other.x, y - other.y };
	}

	template<typename T>
	Vec2 operator*(const T& other)
	{
		return Vec2{ x * other, y * other };
	}

	template<typename T>
	friend Vec2 operator*(const T& lhs, const Vec2& rhs);

public:
	float x;
	float y;

};

template<typename T>
Vec2 operator*(const T& lhs, const Vec2& rhs)
{
	return Vec2{lhs * rhs.x, lhs * rhs.y};
}