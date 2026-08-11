#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "MatrixStack.h"
#include "Camera.h"

extern float gResolutionX;
extern float gResolutionY;

namespace
{
	Matrix4 GetScreenTransform()
	{
		const float hw = gResolutionX * 0.5f;
		const float hh = gResolutionY * 0.5f;
		return
		{
			hw, 0,   0, 0,
			0,  -hh, 0, 0,
			0,  0,   1, 0,
			hw, hh,  0, 1
		};
	}
	Vector3 CreateFaceNormal(const std::vector<Vertex>& triangle)
	{
		const Vector3 a = triangle[0].pos;
		const Vector3 b = triangle[1].pos;
		const Vector3 c = triangle[2].pos;
		Vector3 norm = MathHelper::Normalize(MathHelper::Cross((b - a), (c - a)));
		return norm;
	}
	bool CullTriangle(CullMode mode, const std::vector<Vertex>& triangle)
	{
		if (mode == CullMode::NONE)
		{
			return false;
		}
		Vector3 faceNormal = CreateFaceNormal(triangle);
		if (mode == CullMode::BACK)
		{
			return faceNormal.z > 0;
		}
		else
		{
			return faceNormal.z < 0;
		}
	}
}

PrimativesManager::PrimativesManager() {}

PrimativesManager* PrimativesManager::Get()
{
	static PrimativesManager sInstance;
	return &sInstance;
}

void PrimativesManager::OnNewFrame()
{
	mCullMode = CullMode::BACK;
}

void PrimativesManager::SetCullMode(CullMode cullMode)
{
	mCullMode = cullMode;
}

bool PrimativesManager::BeginDraw(Topology topology, bool applyTransform)
{
	mVertexBuffer.clear();
	mTopology = topology;
	mApplyTransform = applyTransform;
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

	Matrix4 matWorld = MatrixStack::Get()->GetTransform();

	Matrix4 matView = Camera::Get()->GetViewMatrix();

	Matrix4 matProj = Camera::Get()->GetProjectionMatrix();

	Matrix4 matScreen = GetScreenTransform();

	//Matrix4 matFinal = matWorld * matView * matProj * matScreen;

	Matrix4 matNDCSpace = matWorld * matView * matProj;

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

			if (mApplyTransform)
			{
				for (size_t j = 0; j < triangle.size(); j++)
				{
					triangle[j].pos = MathHelper::TransformCoord(triangle[j].pos, matNDCSpace);
				}

				if (CullTriangle(mCullMode, triangle))
				{
					continue;
				}

				for (size_t j = 0; j < triangle.size(); j++)
				{
					triangle[j].pos = MathHelper::TransformCoord(triangle[j].pos, matScreen);
					MathHelper::FlattenVectorScreenCoord(triangle[j].pos);
				}
			}

			if (!Clipper::Get()->ClipTriangle(triangle));
			{
				for (UINT32 t = 2; t < triangle.size(); ++t)
				{
					Rasterizer::Get()->DrawTriangle(triangle[0], triangle[t - 1], triangle[t]);
				}
			}
		}
	}
	break;
	default:
		break;
	}
}