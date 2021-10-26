#include "Cloud.h"


void CCloud::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_CLOUD)->Render(x, y);
	RenderBoundingBox();
}

void CCloud::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - 0 / 2;
	t = y - 0 / 2;
	r = l + 0;
	b = t + 0;
}