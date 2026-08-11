#pragma once

#include "Vertex.h"

enum class Topology
{
	Point,
	Line,
	Triangle
};

enum class CullMode
{
	NONE,
	BACK,
	FRONT
};

class PrimativesManager
{
public:
	static PrimativesManager* Get();

	void OnNewFrame();

	void SetCullMode(CullMode cullMode);

	bool BeginDraw(Topology topology, bool applyTransform);

	void AddVertex(const Vertex& v);

	void EndDraw();

private:
	PrimativesManager();

	std::vector<Vertex> mVertexBuffer;
	Topology mTopology = Topology::Point;
	CullMode mCullMode = CullMode::NONE;
	bool mDrawBegin = false;
	bool mApplyTransform = false;
};