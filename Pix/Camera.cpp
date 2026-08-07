#include "Camera.h"

extern float gResolutionX;
extern float gResolutionY;

Camera* Camera::Get()
{
	static Camera sInstance;
	return &sInstance;
}

void Camera::OnNewFrame()
{
	mPosition = { 0,0,0 };
	mDirection = { 0,0,1 };
	mNearPlane = 0.01f;
	mNearPlane = 100;
	mFOV = 1.57f;
}

void Camera::SetPosition(const Vector3& pos)
{
	mPosition = pos;
}

void Camera::SetDirection(const Vector3& dir)
{
	mDirection = MathHelper::Normalize(dir);
}

void Camera::SetNearPlane(float nearPlane)
{
	mNearPlane = nearPlane;
}

void Camera::SetFarPlane(float farPlane)
{
	mFarPlane = farPlane;
}

void Camera::SetFOV(float fov)
{
	mFOV = fov;
}

Matrix4 Camera::GetViewMatrix() const
{
	const Vector3 l = mDirection;
	const Vector3 r = MathHelper::Normalize(MathHelper::Cross({ 0, 1, 0 }, l));
	const Vector3 u = MathHelper::Normalize(MathHelper::Cross(l, r));
	const float a = -MathHelper::Dot(r, mPosition);
	const float b = -MathHelper::Dot(u, mPosition);
	const float c = -MathHelper::Dot(l, mPosition);
	return{
		r.x, u.x, l.x, 0,
		r.y, u.y, l.y, 0,
		r.z, u.z, l.z, 0,
		  a,   b,   c, 0
	};
}

Matrix4 Camera::GetProjectionMatrix() const
{
	const float a = gResolutionX / gResolutionY;
	const float d = 1 / tanf(mFOV * 0.5f);
	const float w = d / a;
	const float zn = mNearPlane;
	const float zf = mFarPlane;
	const float q = zf / (zf - zn);
	return{
		w, 0, 0,	 0,
		0, d, 0,	 0,
		0, 0, q,	 1,
		0, 0, -zn*q, 0
	};
}

const Vector3& Camera::GetPosition() const
{
	return mPosition;
}

const Vector3& Camera::GetDirection() const
{
	return mDirection;
}