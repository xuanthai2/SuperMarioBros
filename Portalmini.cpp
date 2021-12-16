#include "Portalmini.h"

CPortalmini::CPortalmini(float l, float t, float r, float b, int gx, int gy)
{
	this->gx = gx;
	this->gy = gy;
	x = l;
	y = t;
	width = r - l;
	height = b - t;
}

void CPortalmini::Render()
{
	//RenderBoundingBox();
}

void CPortalmini::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}