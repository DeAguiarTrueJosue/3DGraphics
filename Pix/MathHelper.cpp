#include "MathHelper.h"
#include <cmath>

bool MathHelper::CheckEqual(float a, float b)
{
	return abs((float)(a - b)) < 0.001f;
}

float MathHelper::MagnetudeSquared(const Vector2& v)
{
	return v.x * v.x + v.y * v.y;
}
float MathHelper::MagnetudeSquared(const Vector3& v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

float MathHelper::Magnetude(const Vector2& v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}
float MathHelper::Magnetude(const Vector3& v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector2 MathHelper::Normalize(const Vector2& v)
{
	return v / Magnetude(v);
}
Vector3 MathHelper::Normalize(const Vector3& v)
{
	return v / Magnetude(v);
}

float MathHelper::Dot(const Vector2& a, Vector2& b)
{
	return a.x * b.x + a.y * b.y;
}
float MathHelper::Dot(const Vector3& a, Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 MathHelper::Cross(const Vector3& a, const Vector3& b)
{
	return{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}