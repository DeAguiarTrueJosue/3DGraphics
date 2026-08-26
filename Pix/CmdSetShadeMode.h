#pragma once

#include "Command.h"

class CmdSetShadeMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetShadeMode";
	}

	const char* GetDescription() override
	{
		return
			"SetShadeMode(ShadeMode)\n"
			"\n"
			"- Sets the shade mode for the frame"
			"\n- shade mode (flat, gouraud, phong)";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
