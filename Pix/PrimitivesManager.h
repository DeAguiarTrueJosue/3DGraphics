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

class PrimitivesManager
{
public:
	static PrimitivesManager* Get();

	void OnNewFrame();

	void SetCullMode(CullMode cullMode);

	void SetCorrectUV(bool correctUV);

	bool BeginDraw(Topology topology, bool applyTransform);

	void AddVertex(const Vertex& v);

	void EndDraw();

private:
	PrimitivesManager();

	std::vector<Vertex> mVertexBuffer;
	Topology mTopology = Topology::Point;
	CullMode mCullMode = CullMode::NONE;
	bool mDrawBegin = false;
	bool mApplyTransform = false;
	bool mCorrectUV = false;
};