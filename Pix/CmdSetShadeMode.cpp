#include "CmdSetShadeMode.h"
#include "Rasterizer.h"

bool CmdSetShadeMode::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	ShadeMode shade = ShadeMode::Flat;

	if (params[0] == "flat") { shade = ShadeMode::Flat; }
	else if (params[0] == "gouraud") { shade = ShadeMode::Gouraud; }
	else if (params[0] == "phong") { shade = ShadeMode::Phong; }
	else { return false; }

	Rasterizer::Get()->SetShadeMode(shade);
	return true;
}
