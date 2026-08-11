#pragma once

#include "Command.h"

class CmdSetCullMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetCullMode";
	}

	const char* GetDescription() override
	{
		return
			"SetCullMode(cullMode)\n"
			"\n"
		"- Sets cull mode for rendering\n";
		"- cullMode (none, back, front)";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
