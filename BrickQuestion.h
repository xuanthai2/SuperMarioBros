#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICKQUESTION 12000
#define ID_ANI_BRICKQUESTION_DIE 12001
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define BRICKQUESTION_LIVE 200
#define BRICKQUESTION_DIE 300



class CBrickQuestion : public CGameObject {

public:
	CBrickQuestion(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

