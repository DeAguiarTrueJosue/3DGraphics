#pragma once
#include "Command.h"
class CmdSetLightAmbient : public Command {
public:
	const char* GetName() override {
		return "SetLightAmbient";
	}
	const char* GetDescription() override {
		return
			"SetLightAmbient(r, g, b)\n"
			"- set the ambient color of the light";
	}
	bool Execute(const std::vector<std::string>& params) override;
};
class CmdSetLightDiffuse : public Command {
public:
	const char* GetName() override {
		return "SetLightDiffuse";
	}
	const char* GetDescription() override {
		return
			"SetLightDiffuse(r, g, b)\n"
			"- set the diffuse color of the light";
	}
	bool Execute(const std::vector<std::string>& params) override;
};
class CmdSetLightSpecular : public Command {
public:
	const char* GetName() override {
		return "SetLightSpecular";
	}
	const char* GetDescription() override {
		return
			"SetLightSpecular(r, g, b)\n"
			"- set the specular color of the light";
	}
	bool Execute(const std::vector<std::string>& params) override;
};
class CmdAddDirectionalLight : public Command {
public:
	const char* GetName() override {
		return "AddDirectionalLight";
	}
	const char* GetDescription() override {
		return
			"AddDirectionalLight(x, y, z)\n"
			"- add a directinal light to the scene";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdAddPointLight : public Command {
public:
	const char* GetName() override {
		return "AddPointLight";
	}
	const char* GetDescription() override {
		return
			"AddPointLight(x, y, z, <constant>, <linear>, <quadratic>)\n"
			"- add a point light to the scene at a specific position\n"
			"- can modify the attenuation constants";
	}
	bool Execute(const std::vector<std::string>& params) override;
};

class CmdAddSpotLight : public Command {
public:
	const char* GetName() override {
		return "AddSpotLight";
	}
	const char* GetDescription() override {
		return
			"AddSpotLight(px, py, pz, dx, dy, dz, <constant>, <linear>, <quadratic>, <angle>, <decay>)\n"
			"- add a spot light to the scene at a specific position\n"
			"- can modify the attenuation constants";
	}
	bool Execute(const std::vector<std::string>& params) override;
};