#include "RayTracer.h"
#include "Camera.h"
#include <math.h>

extern float gResolutionX;
extern float gResolutionY;

RayTracer* RayTracer::Get()
{
	static RayTracer sInstance;
	return &sInstance;
}

void RayTracer::OnNewFrame()
{
	mObjects.clear();
	mLights.clear();
}

bool RayTracer::BeginDraw()
{
	return true;
}

void RayTracer::AddObject(const Sphere& sphere, const X::Color& color, float ri)
{
	mObjects.push_back({ sphere, color, ri });
}

void RayTracer::AddLight(const Vector3& position, const X::Color& color)
{
	mLights.push_back({ position, color });
}

bool RayTracer::EndDraw()
{
	return true;
}

X::Color RayTracer::Trace(const Ray& ray, float depth)
{
	return X::Color();
}
