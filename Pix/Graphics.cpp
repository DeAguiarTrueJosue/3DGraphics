#include "Graphics.h"

#include "Viewport.h"
#include "Clipper.h"

void Graphics::NewFrame()
{
	Viewport::Get()->OnNewFrame();
	Clipper::Get()->OnNewFrame();

	Matrix4 matTrans = Matrix4::Translation(4, 10, 5);
	Matrix4 matRotX = Matrix4::RotationX(45 * MathHelper::DegToRad);
	Matrix4 matRotY = Matrix4::RotationY(15 * MathHelper::DegToRad);
	Matrix4 matFinal = matRotX * matRotY * matTrans;
	Matrix4 matInv = MathHelper::Inverse(matFinal);
	Matrix4 matIdentity = matFinal * matInv;
	int hi = 0;
	++hi;
}