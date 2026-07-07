#include "CmdDrawSquare.h"

#include "Rasterizer.h"
#include "VariableCache.h"

bool CmdDrawSquare::Execute(const std::vector<std::string>& params)
{
	// Need at least 4 params for left, top, right, bottom
	if (params.size() < 4)
		return false;

	int left = VariableCache::Get()->GetFloat(params[0]);
	int top = VariableCache::Get()->GetFloat(params[1]);
	int right = VariableCache::Get()->GetFloat(params[2]);
	int bottom = VariableCache::Get()->GetFloat(params[3]);

	// Draw the pixels
	for (int x = left; x <= right; x++)
	{
		for (int y = top; y <= bottom; y++)
		{
			Rasterizer::Get()->DrawPoint(x, y);
		}
	}
	return true;
}
