#include "CmdSetColor.h"

#include "Rasterizer.h"
#include "VariableCache.h"

bool CmdSetColor::Execute(const std::vector<std::string>& params)
{
	// we need 3 vqlues: r, g, b
	if (params.size() < 3)
	{
		return false;
	}

	float r = VariableCache::Get()->GetFloat(params[0]);
	float g = VariableCache::Get()->GetFloat(params[1]);
	float b = VariableCache::Get()->GetFloat(params[2]);

	Rasterizer::Get()->SetColor({ r, g, b, 1.0f });
	return true;
}
