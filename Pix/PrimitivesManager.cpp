#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"

PrimativesManager::PrimativesManager() {}

PrimativesManager* PrimativesManager::Get()
{
	static PrimativesManager sInstance;
	return &sInstance;
}

bool PrimativesManager::BeginDraw(Topology topology)
{
	mVertexBuffer.clear();
	mTopology = topology;
	mDrawBegin = true;
	return true;
}

void PrimativesManager::AddVertex(const Vertex& v)
{
	if (mDrawBegin)
	{
		mVertexBuffer.push_back(v);
	}
}

void PrimativesManager::EndDraw()
{
	if (!mDrawBegin)
	{
		return;
	}

	switch (mTopology)
	{
	case Topology::Point:
	{
		for (UINT32 i = 0; i < mVertexBuffer.size(); i++)
		{
			if (!Clipper::Get()->ClipPoint(mVertexBuffer[i]))
			{
				Rasterizer::Get()->DrawPoint(mVertexBuffer[i]);
			}
		}
	}
	break;
	case Topology::Line:
	{
		for (UINT32 i = 1; i < mVertexBuffer.size(); i += 2)
		{
			if (!Clipper::Get()->ClipLine(mVertexBuffer[i - 1], mVertexBuffer[i]))
			{
				Rasterizer::Get()->DrawLine(mVertexBuffer[i - 1], mVertexBuffer[i]);
			}
		}
	}
	break;
	case Topology::Triangle:
	{
		for (UINT32 i = 2; i < mVertexBuffer.size(); i += 3)
		{
			std::vector<Vertex> triangle{ mVertexBuffer[i - 2], mVertexBuffer[i - 1], mVertexBuffer[i] };
			if (!Clipper::Get()->ClipTriangle(triangle));
			{
				for (UINT32 t = 2; t < triangle.size(); ++t)
				{
					Rasterizer::Get()->DrawTriangle(triangle[0], triangle[t-1], triangle[t]);
				}
			}
		}
	}
	break;
	default:
		break;
	}
}