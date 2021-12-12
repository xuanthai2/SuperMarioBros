#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16
#define BRICK_TYPE_NORMAL 0
#define BRICK_TYPE_P 1
#define BRICK_TYPE_STAND 2
#define BRICK_STATE_LIVE 1333
#define BRICK_STATE_DIE 1334
#define BRICK_STATE_STAND 1335
class CBrick : public CGameObject {
public:
	int inside;

	CBrick(float x, float y,int i) : CGameObject(x, y) {
		this->inside = i;
		if (inside == BRICK_TYPE_P)
			state = BRICK_STATE_LIVE;
		else if (inside == BRICK_TYPE_NORMAL)
			state = BRICK_STATE_DIE;
		else if (inside == BRICK_TYPE_STAND)
			state = BRICK_STATE_STAND;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 1; }
	virtual int IsCollidable() { return 1; };
	virtual int IsSpecial() { return 0; }
	virtual void SetState(int state);

	int GetInside() { return inside; }
};