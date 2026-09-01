#include "CmdRayTrace.h"
#include "RayTracer.h"
#include "VariableCache.h"

bool CmdBeginRayTracing::Execute(const std::vector<std::string>& params)
{
	return RayTracer::Get()->BeginDraw();
}

bool CmdEndRayTracing::Execute(const std::vector<std::string>& params)
{
	return RayTracer::Get()->EndDraw();
}

bool CmdRTSphere::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 7)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();

	const float x = vc->GetFloat(params[0]);
	const float y = vc->GetFloat(params[1]);
	const float z = vc->GetFloat(params[2]);
	const float radius = vc->GetFloat(params[3]);
	const float r = vc->GetFloat(params[4]);
	const float g = vc->GetFloat(params[5]);
	const float b = vc->GetFloat(params[6]);
	const float ri = (params.size() > 7) ? vc->GetFloat(params[7]) : 0.0f;

	RayTracer::Get()->AddObject({ {x, y, z}, radius }, { r, g, b ,1.0f }, ri);

	return true;
}

bool CmdRTLight::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 6)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();

	const float x = vc->GetFloat(params[0]);
	const float y = vc->GetFloat(params[1]);
	const float z = vc->GetFloat(params[2]);
	const float r = vc->GetFloat(params[3]);
	const float g = vc->GetFloat(params[4]);
	const float b = vc->GetFloat(params[5]);

	RayTracer::Get()->AddLight({x, y, z}, { r, g, b ,1.0f });

	return true;
}
