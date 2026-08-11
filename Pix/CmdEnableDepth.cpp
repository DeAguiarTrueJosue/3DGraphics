#include "CmdEnableDepth.h"

#include "DepthBuffer.h"
#include "VariableCache.h"

bool CmdEnableDepth::Execute(const std::vector<std::string>& params)
{
	// Need at leaset 3 params for name, =, value
	if (params.size() < 1)
		return false;

	DepthBuffer::Get()->SetEnable(VariableCache::Get()->GetBool(params[0]));

	return true;
}
