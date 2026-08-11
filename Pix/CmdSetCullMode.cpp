#include "CmdSetCullMode.h"

#include "PrimitivesManager.h"

bool CmdSetCullMode::Execute(const std::vector<std::string>&params)
{
	if (params.size() < 1)
	{
		return false;
	}

	CullMode cullMode = CullMode::NONE;

	if (params[0] == "none") { cullMode = CullMode::NONE; }
	else if (params[0] == "back") { cullMode = CullMode::BACK; }
	else if (params[0] == "front") { cullMode = CullMode::FRONT; }
	else { return false; }

	PrimativesManager::Get()->SetCullMode(cullMode);
	return true;
}
