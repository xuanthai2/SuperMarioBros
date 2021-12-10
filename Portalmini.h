#pragma once

#include "GameObject.h"

class CPortalmini : public CGameObject
{
	float gx;
	float gy;

	float width;
	float height;

public:
	CPortalmini(float l, float t, float r, float b, int gx , int gy);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int Getgx() { return gx; }
	int Getgy() { return gy; }
};

