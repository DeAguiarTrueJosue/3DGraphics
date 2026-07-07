#pragma once

#include "Vector2.h"
#include "Vector3.h"

namespace MathHelper
{
	constexpr float DegToRad = 3.1415926 / 180;
	constexpr float RadToDeg = 180 / 3.1415926;

	bool CheckEqual(float a, float b);

	float MagnetudeSquared(const Vector2& v);
	float MagnetudeSquared(const Vector3& v);

	float Magnetude(const Vector2& v);
	float Magnetude(const Vector3& v);

	Vector2 Normalize(const Vector2& v);
	Vector3 Normalize(const Vector3& v);

	float Dot(const Vector2& a, Vector2& b);
	float Dot(const Vector3& a, Vector3& b);

	Vector3 Cross(const Vector3& a, const Vector3& b);
}