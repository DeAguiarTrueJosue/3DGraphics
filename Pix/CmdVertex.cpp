#include "CmdVertex.h"

#include "PrimitivesManager.h"
#include "VariableCache.h"

bool CmdVertex::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 2)
	{
		return false;
	}

	Vertex v;
	v.pos = Vector3(0, 0, 0);
	v.color = X::Color(1, 1, 1, 1);
	v.pos.x = VariableCache::Get()->GetFloat(params[0]);
	v.pos.y = VariableCache::Get()->GetFloat(params[1]);

	if (params.size() == 2)
	{

	}
	else if (params.size() == 3)
	{
		v.pos.z = VariableCache::Get()->GetFloat(params[2]);
	}
	else if (params.size() == 5) {
		v.color.r = VariableCache::Get()->GetFloat(params[2]);
		v.color.g = VariableCache::Get()->GetFloat(params[3]);
		v.color.b = VariableCache::Get()->GetFloat(params[4]);
	}
	else if (params.size() == 6) {
		v.pos.z = VariableCache::Get()->GetFloat(params[2]);
		v.color.r = VariableCache::Get()->GetFloat(params[3]);
		v.color.g = VariableCache::Get()->GetFloat(params[4]);
		v.color.b = VariableCache::Get()->GetFloat(params[5]);
	}
	else {
		return false;
	}


	PrimativesManager::Get()->AddVertex(v);
	return true;
}
