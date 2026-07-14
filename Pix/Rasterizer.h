#pragma once

#include <XEngine.h>
#include "Vertex.h"

enum class FillMode
{
	WireFrame,
	Solid
};

class Rasterizer
{
public:
	static Rasterizer* Get();

public:
	void SetColor(X::Color color);
	void SetFillMode(FillMode fillMode);

	void DrawPoint(int x, int y);

	void DrawPoint(const Vertex& v);
	void DrawLine(const Vertex& a, const Vertex& b);
	void DrawTriangle(const Vertex& a, const Vertex& b, const Vertex& c);

private:
	X::Color mColor = X::Colors::White;
	FillMode mFillMode = FillMode::WireFrame;

	void DrawFilledTriangle(const Vertex& a, const Vertex& b, const Vertex& c);
};