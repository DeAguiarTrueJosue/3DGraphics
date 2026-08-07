#include "CmdCamera.h"
#include "VariableCache.h"
#include "Camera.h"

bool CmdSetCameraPosition::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();
	const float x = vc->GetFloat(params[0]);
	const float y = vc->GetFloat(params[1]);
	const float z = vc->GetFloat(params[2]);
	Camera::Get()->SetPosition({x, y, z});
	return true;
}

bool CmdSetCameraDirection::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 3)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();
	const float x = vc->GetFloat(params[0]);
	const float y = vc->GetFloat(params[1]);
	const float z = vc->GetFloat(params[2]);
	Camera::Get()->SetDirection({ x, y, z });
	return true;
}

bool CmdSetCameraNear::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();
	const float n = vc->GetFloat(params[0]);
	Camera::Get()->SetNearPlane(n);
	return true;
}

bool CmdSetCameraFar::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();
	const float f = vc->GetFloat(params[0]);
	Camera::Get()->SetFarPlane(f);
	return true;
}

bool CmdSetCameraFOV::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	VariableCache* vc = VariableCache::Get();
	const float f = vc->GetFloat(params[0]);
	Camera::Get()->SetFOV(f * MathHelper::DegToRad);
	return true;
}