#pragma once

#include "Command.h"

class CmdSetMaterialEmissive : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialEmissive";
	}

	const char* GetDescription() override
	{
		return "SetMaterialEmissive(r, g, b)\n"
			"\n"
			"- sets the rgb values for the material emissive level";
	}
	bool Execute(const std::vector<std::string>& params);
};

class CmdSetMaterialAmbient : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialAmbient";
	}

	const char* GetDescription() override
	{
		return "SetMaterialAmbient(r, g, b)\n"
			"\n"
			"- sets the rgb values for the material ambient level";
	}
	bool Execute(const std::vector<std::string>& params);
};

class CmdSetMaterialDiffuse : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialDiffuse";
	}

	const char* GetDescription() override
	{
		return "SetMaterialDiffuse(r, g, b)\n"
			"\n"
			"- sets the rgb values for the material diffuse level";
	}
	bool Execute(const std::vector<std::string>& params);
};

class CmdSetMaterialSpecular : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialSpecular";
	}

	const char* GetDescription() override
	{
		return "SetMaterialSpecular(r, g, b)\n"
			"\n"
			"- sets the rgb values for the material specular level";
	}
	bool Execute(const std::vector<std::string>& params);
};

class CmdSetMaterialShininess : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialShininess";
	}

	const char* GetDescription() override
	{
		return "SetMaterialShininess(float)\n"
			"\n"
			"- sets the rgb values for the material shininess level";
	}
	bool Execute(const std::vector<std::string>& params);
};