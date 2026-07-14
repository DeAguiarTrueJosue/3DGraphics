#include "PrimitivesManager.h"
#include "Rasterizer.h"

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
			Rasterizer::Get()->DrawPoint(mVertexBuffer[i]);
		}
	}
	break;
	case Topology::Line:
	{
		for (UINT32 i = 1; i < mVertexBuffer.size(); i += 2)
		{
			Rasterizer::Get()->DrawLine(mVertexBuffer[i - 1], mVertexBuffer[i]);
		}
	}
	break;
	case Topology::Triangle:
	{
		for (UINT32 i = 2; i < mVertexBuffer.size(); i += 3)
		{
			Rasterizer::Get()->DrawTriangle(mVertexBuffer[i - 2], mVertexBuffer[i - 1], mVertexBuffer[i]);
		}
	}
	break;
	default:
		break;
	}
}