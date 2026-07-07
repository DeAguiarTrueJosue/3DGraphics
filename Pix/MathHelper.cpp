#include "MathHelper.h"
#include <cmath>

bool CheckEqual(float a, float b)
{
	return abs((float)(a - b)) < 0.001f;
}

float MagnetudeSquared(const Vector2& v)
{
	return v.x * v.x + v.y * v.y;
}
float MagnetudeSquared(const Vector3& v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

float Magnetude(const Vector2& v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}
float Magnetude(const Vector3& v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector2 Normalize(const Vector2& v)
{
	return v / Magnetude(v);
}
Vector3 Normalize(const Vector3& v)
{
	return v / Magnetude(v);
}

float Dot(const Vector2& a, Vector2& b)
{
	return a.x * b.x + a.y * b.y;
}
float Dot(const Vector3& a, Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Cross(const Vector3& a, const Vector3& b)
{
	return{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}