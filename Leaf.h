#pragma once
#include "GameObject.h"

#define LEAF_GRAVITY 0.003f
#define LEAF_BOUNCE_SPEED 0.2f

#define ID_ANI_LEAF 21112


#define LEAF_STATE_IDLE 120
#define LEAF_STATE_BOUNCE 121

#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 16


class CLeaf : public CGameObject {
protected:
	float ax;
	float ay;

public:
	CLeaf(float x, float y) : CGameObject(x, y) {
		this->ax = 0;
		this->ay = 0;
		vx = 0;
		vy = 0;
		SetState(LEAF_STATE_IDLE);
	}

	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);



	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual int IsSpecial() { return 0; }
	virtual void SetState(int state);
};

