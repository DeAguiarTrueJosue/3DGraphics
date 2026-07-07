#pragma once

#include "Command.h"

class CmdDrawSquare: public Command
{
public:

	const char* GetName() override
	{
		return "DrawSquare";
	}
	const char* GetDescription() override
	{
		return "DrawSquare(left, top, right, bottom)\n"
			"\n"
			"- Draw a square from the col left to the col right"
			"and the from row top to the row bottom\n";
	}
	bool Execute(const std::vector<std::string>& params) override;
};