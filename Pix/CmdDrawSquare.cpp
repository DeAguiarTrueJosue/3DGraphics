#include "CmdDrawSquare.h"

#include "Rasterizer.h"

bool CmdDrawSquare::Execute(const std::vector<std::string>& params)
{
	// Need at least 4 params for left, top, right, bottom
	if (params.size() < 4)
		return false;

	int left = stoi(params[0]);
	int top = stoi(params[1]);
	int right = stoi(params[2]);
	int bottom = stoi(params[3]);

	// Draw the pixel
	for (int x = left; x <= right; x++)
	{
		for (int y = top; y <= bottom; y++)
		{
			Rasterizer::Get()->DrawPoint(x, y);
		}
	}
	return true;
}
