#pragma once

#include "Command.h"

class CmdSetAddressMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetAddressMode";
	}

	const char* GetDescription() override
	{
		return
			"SetAddressMode(mode)\n"
			""
			"\n- sets address mode for uv coordinates"
			"\n- mode (border, clamp, wrap, mirror)";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
