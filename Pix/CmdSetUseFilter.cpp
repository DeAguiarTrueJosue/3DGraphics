#include "CmdSetUseFilter.h"
#include "VariableCache.h"
#include "TextureManager.h"

bool CmdSetUseFilter::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	TextureManager::Get()->SetUseFilter(VariableCache::Get()->GetBool(params[0]));
	return true;
}
