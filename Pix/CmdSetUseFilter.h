#pragma once

#include "Command.h"

class CmdSetUseFilter : public Command
{
public:
	const char* GetName() override
	{
		return "SetUseFilter";
	}

	const char* GetDescription() override
	{
		return
			"SetUseFilter(useFilter)\n"
			"\n"
			"- Sets if should use filter for the textures";
	}

	bool Execute(const std::vector<std::string>& params) override;
};