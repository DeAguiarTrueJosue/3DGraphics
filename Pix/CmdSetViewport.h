#pragma once

#include "Command.h"

class CmdSetViewport : public Command
{
public:
	const char* GetName() override
	{
		return "SetViewport";
	}

	const char* GetDescription() override
	{
		return
			"SetViewport(X, Y, width, height, <show>)\n"
			"\n"
			"- Create a viewport rect with x, y, width and height";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
