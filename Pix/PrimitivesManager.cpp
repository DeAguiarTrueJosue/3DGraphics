#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "MatrixStack.h"
#include "Camera.h"
#include "LightManager.h"

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

PrimitivesManager::PrimitivesManager() {}

PrimitivesManager* PrimitivesManager::Get()
{
	static PrimitivesManager sInstance;
	return &sInstance;
}

void PrimitivesManager::OnNewFrame()
{
	mCullMode = CullMode::BACK;
	mCorrectUV = false;
}

void PrimitivesManager::SetCullMode(CullMode cullMode)
{
	mCullMode = cullMode;
}

void PrimitivesManager::SetCorrectUV(bool correctUV)
{
	mCorrectUV = correctUV;
}

bool PrimitivesManager::BeginDraw(Topology topology, bool applyTransform)
{
	mVertexBuffer.clear();
	mTopology = topology;
	mApplyTransform = applyTransform;
	mDrawBegin = true;
	return true;
}

void PrimitivesManager::AddVertex(const Vertex& v)
{
	if (mDrawBegin)
	{
		mVertexBuffer.push_back(v);
	}
}

void PrimitivesManager::EndDraw()
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

	Matrix4 matNDCSpace = matView * matProj;

	ShadeMode shadeMode = Rasterizer::Get()->GetShadeMode();

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

				if (MathHelper::CheckEqual(MathHelper::MagnetudeSquared(triangle[0].normal), 0))
				{
					Vector3 faceNorm = CreateFaceNormal(triangle);

					for (size_t j = 0; j < triangle.size(); j++)
					{
						triangle[j].normal = faceNorm;
					}
				}

				for (size_t j = 0; j < triangle.size(); j++)
				{
					triangle[j].pos = MathHelper::TransformCoord(triangle[j].pos, matWorld);
					triangle[j].worldPos = triangle[j].pos;
					triangle[j].normal = MathHelper::TransformNormal(triangle[j].normal, matWorld);
				}
				if (triangle[0].color.z >= 0)
				{
					if (shadeMode == ShadeMode::Flat)
					{
						X::Color lightColor = LightManager::Get()->ComputeLightColor(triangle[0].pos, triangle[0].normal);
						triangle[0].color *= lightColor;
						triangle[1].color *= lightColor;
						triangle[2].color *= lightColor;
					}
					else if (shadeMode == ShadeMode::Gouraud)
					{
						for (size_t j = 0; j < triangle.size(); j++)
						{
							triangle[j].color *= LightManager::Get()->ComputeLightColor(triangle[j].pos, triangle[j].normal);
						}
					}
				}
				else if (mCorrectUV)
				{
					for (uint32_t j = 0; j < triangle.size(); j++)
					{
						Vector3 viewSpace = MathHelper::TransformCoord(triangle[j].worldPos, matView);
						triangle[j].color.x /= viewSpace.z;
						triangle[j].color.y /= viewSpace.z;
						triangle[j].color.w = 1.0f / viewSpace.z;
					}
				}

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