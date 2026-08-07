#pragma once

#include "Vertex.h"

enum class Topology
{
	Point,
	Line,
	Triangle
};

class PrimativesManager
{
public:
	static PrimativesManager* Get();

	bool BeginDraw(Topology topology, bool applyTransform);

	void AddVertex(const Vertex& v);

	void EndDraw();

private:
	PrimativesManager();

	std::vector<Vertex> mVertexBuffer;
	Topology mTopology = Topology::Point;
	bool mDrawBegin = false;
	bool mApplyTransform = false;
};