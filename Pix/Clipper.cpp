#include "Clipper.h"
#include "Viewport.h"

const short BIT_INSIDE		= 0;
const short BIT_LEFT		= 1 << 0;
const short BIT_RIGHT		= 1 << 1;
const short BIT_BOTTOM		= 1 << 2;
const short BIT_TOP			= 1 << 3;


short GetOutputCode(float x, float y)
{
	Viewport* vp = Viewport::Get();
	short code = BIT_INSIDE;
	if (x < vp->GetMinX())
	{
		code |= BIT_LEFT;
	}
	else if (x > vp->GetMaxX())
	{
		code |= BIT_RIGHT;
	}
	if (y < vp->GetMinY())
	{
		code |= BIT_TOP;
	}
	else if (y > vp->GetMaxY())
	{
		code |= BIT_BOTTOM;
	}

	return code;
}

enum ClipEdge
{
	CE_LEFT,
	CE_TOP,
	CE_RIGHT,
	CE_BOTTOM,
	CE_COUNT
};

bool IsInFront(ClipEdge edge, const Vector3& pos)
{
	Viewport* vp = Viewport::Get();

	switch (edge)
	{
	case CE_LEFT:	return pos.x > vp->GetMinX();
	case CE_TOP:	return pos.y > vp->GetMinY();
	case CE_RIGHT:	return pos.x < vp->GetMaxX();
	case CE_BOTTOM: return pos.y < vp->GetMaxY();
	case CE_COUNT:
		break;
	default:
		break;
	}
	return false;
}

Vertex ComputeIntersection(ClipEdge edge, const Vertex& a, const Vertex& b)
{
	Viewport* vp = Viewport::Get();
	float t = 0;

	switch (edge)
	{
	case CE_LEFT:	t = (vp->GetMinX() - a.pos.x) / (b.pos.x - a.pos.x); break;
	case CE_TOP:	t = (vp->GetMinY() - a.pos.y) / (b.pos.y - a.pos.y); break;
	case CE_RIGHT:	t = (vp->GetMaxX() - a.pos.x) / (b.pos.x - a.pos.x); break;
	case CE_BOTTOM: t = (vp->GetMaxY() - a.pos.y) / (b.pos.y - a.pos.y); break;
	case CE_COUNT:
		break;
	default:
		break;
	}
	return LerpVertex(a, b, t);
}

Clipper* Clipper::Get()
{
	static Clipper sInstance;
	return &sInstance;
}

void Clipper::OnNewFrame()
{
	*this = {};
}

bool Clipper::ClipPoint(const Vertex& v)
{
	if (!mIsClipping)
	{
		return false;
	}
	Viewport* vp = Viewport::Get();
	float minx = vp->GetMinX();
	float miny = vp->GetMinY();
	float maxx = vp->GetMaxX();
	float maxy = vp->GetMaxY();
	return v.pos.x < minx || v.pos.x > maxx || v.pos.y < miny || v.pos.y > maxy;
}

bool Clipper::ClipLine(Vertex& a, Vertex& b)
{
	if (!mIsClipping)
	{
		return false;
	}
	Viewport* vp = Viewport::Get();
	float minx = vp->GetMinX();
	float miny = vp->GetMinY();
	float maxx = vp->GetMaxX();
	float maxy = vp->GetMaxY();

	short codeA = GetOutputCode(a.pos.x, a.pos.y);
	short codeB = GetOutputCode(b.pos.x, b.pos.y);

	while (true)
	{
		if (!(codeA | codeB))
		{
			break;
		}
		else if (codeA & codeB)
		{
			break;
		}

		float t = 0;
		short outCode = codeB > codeA ? codeB : codeA;

		if (outCode & BIT_TOP)			{ t = (miny - a.pos.y) / (b.pos.y - a.pos.y); }
		else if (outCode & BIT_BOTTOM)	{ t = (maxy - a.pos.y) / (b.pos.y - a.pos.y); }
		else if (outCode & BIT_LEFT)	{ t = (minx - a.pos.x) / (b.pos.x - a.pos.x); }
		else if (outCode & BIT_RIGHT)	{ t = (maxx - a.pos.x) / (b.pos.x - a.pos.x); }

		if (outCode == codeA)
		{
			a = LerpVertex(a, b, t);
			codeA = GetOutputCode(a.pos.x, a.pos.y);
		}
		else if (outCode == codeB)
		{
			b = LerpVertex(a, b, t);
			codeB = GetOutputCode(b.pos.x, b.pos.y);
		}
	}

	return (codeA | codeB);
}

bool Clipper::ClipTriangle(std::vector<Vertex>& vertices)
{
	if (!mIsClipping)
	{
		return false;
	}

	std::vector<Vertex> newVertices;
	for (int i = 0; i < CE_COUNT; i++)
	{
		newVertices.clear();
		ClipEdge edge = (ClipEdge)i;
		for (int n = 0; n < vertices.size(); n++)
		{
			size_t nP0 = (n + 1) % vertices.size();

			const Vertex& vN = vertices[n];
			const Vertex& vP0 = vertices[nP0];

			bool nIsInFront = IsInFront(edge, vN.pos);
			bool p0IsInFront = IsInFront(edge, vP0.pos);

			if (nIsInFront && p0IsInFront)
			{
				newVertices.push_back(vP0);
			}
			else if (!nIsInFront && !p0IsInFront)
			{

			}
			else if (nIsInFront && !p0IsInFront)
			{
				newVertices.push_back(ComputeIntersection(edge, vN, vP0));
			}else if(!nIsInFront && p0IsInFront)
			{
				newVertices.push_back(ComputeIntersection(edge, vN, vP0));
				newVertices.push_back(vP0);
			}
		}
		vertices = newVertices;
	}
	return newVertices.empty();
}

bool Clipper::IsClipping() const
{
	return mIsClipping;
}

void Clipper::SetClipping(bool enable)
{
	mIsClipping = enable;
}


