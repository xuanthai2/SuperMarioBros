#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_ANI_CLOUD 11100
#define	CLOUD_WIDTH 10
#define CLOUD_BBOX_WIDTH 10
#define CLOUD_BBOX_HEIGHT 16

class CCloud : public CGameObject {
public:
	CCloud(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

};

