#include "CmdSetCorrectUV.h"
#include "VariableCache.h"
#include "PrimitivesManager.h"

bool CmdSetCorrectUV::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	PrimitivesManager::Get()->SetCorrectUV(VariableCache::Get()->GetBool(params[0]));
	return true;
}
