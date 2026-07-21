#include "CmdSetClipping.h"

#include "Clipper.h"

bool CmdSetClipping::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	Clipper::Get()->SetClipping(params[0] == "true");

	return true;
}
