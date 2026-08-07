#pragma once

#include "Command.h"

class CmdBeginDraw : public Command
{
public:
	const char* GetName() override
	{
		return "BeginDraw";
	}

	const char* GetDescription() override
	{
		return
			"BeginDraw(topology, <applyTransform>)\n"
			"\n"
			"- starts storing vertices";
			"- topology (point, line, triangle)";
			"- (optional) apply transform on following drawings";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
