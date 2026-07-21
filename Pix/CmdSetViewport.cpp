#include "CmdSetViewport.h"
#include "Viewport.h"

bool CmdSetViewport::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 4)
	{
		return false;
	}

	int x = std::stof(params[0]);
	int y = std::stof(params[1]);
	int width = std::stof(params[2]);
	int height = std::stof(params[3]);

	bool show = false;

	if (params.size() == 5)
	{
		show = params[4] == "true";
	}

	Viewport::Get()->SetViewport(x, y, width, height);
	Viewport::Get()->ShowViewport(show);

	return true;
}
