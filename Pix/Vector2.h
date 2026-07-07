#pragma once

struct Vector2
{
	float x, y;

	Vector2() : x(0), y(0) {};
	Vector2(float s) : x(s), y(s) {};
	Vector2(float x, float y) : x(x), y(y) {};
	Vector2(Vector2& v) : x(v.x), y(v.y) {};

	//opp

	Vector2 operator-() const { return{ -x, -y }; }
	Vector2 operator+(const Vector2& rhs) const { return{ x + rhs.x, y + rhs.y }; }
	Vector2 operator-(const Vector2& rhs) const { return{ x - rhs.x, y - rhs.y }; }
	Vector2 operator*(const float rhs) const { return{ x * rhs, y * rhs }; }
	Vector2 operator/(const float rhs) const { return{ x / rhs, y / rhs }; }

	Vector2& operator+=(const Vector2& rhs) { x += rhs.x; y += rhs.y; return *this; }
	Vector2& operator-=(const Vector2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
	Vector2& operator*=(const float rhs) { x *= rhs; y *= rhs; return *this; }
	Vector2& operator/=(const float rhs) { x /= rhs; y /= rhs; return *this; }
};