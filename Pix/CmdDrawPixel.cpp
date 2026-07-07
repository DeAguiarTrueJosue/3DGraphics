#include "CmdDrawPixel.h"

#include "Rasterizer.h"
#include "VariableCache.h"

bool CmdDrawPixel::Execute(const std::vector<std::string>& params)
{
	// Need at least 2 params for x, y
	if (params.size() < 2)
		return false;

	int positionX = VariableCache::Get()->GetFloat(params[0]);
	int positionY = VariableCache::Get()->GetFloat(params[1]);

	// Draw the pixel
	Rasterizer::Get()->DrawPoint(positionX, positionY);
	return true;
}
