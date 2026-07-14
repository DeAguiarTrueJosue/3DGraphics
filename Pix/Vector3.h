#pragma once

struct Vector3
{
	float x, y, z;

	Vector3() : x(0), y(0), z(0) {};
	Vector3(float s) : x(s), y(s), z(s) {};
	Vector3(float x, float y) : x(x), y(y), z(0) {};
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {};
	Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {};

	//opp

	Vector3 operator-() const { return{ -x, -y, -z }; }
	Vector3 operator+(const Vector3& rhs) const { return{ x + rhs.x, y + rhs.y, z + rhs.z }; }
	Vector3 operator-(const Vector3& rhs) const { return{ x - rhs.x, y - rhs.y, z - rhs.z }; }
	Vector3 operator*(const float rhs) const { return{ x * rhs, y * rhs, z * rhs }; }
	Vector3 operator/(const float rhs) const { return{ x / rhs, y / rhs, z / rhs }; }

	Vector3& operator+=(const Vector3& rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
	Vector3& operator-=(const Vector3& rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
	Vector3& operator*=(const float rhs) { x *= rhs; y *= rhs; z *= rhs; return *this; }
	Vector3& operator/=(const float rhs) { x /= rhs; y /= rhs; z /= rhs; return *this; }
};