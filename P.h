#pragma once


#include "GameObject.h"

#define LEAF_GRAVITY 0.0001f
#define P_BBOX_WIDTH 15
#define P_BBOX_HEIGHT 15

#define P_STATE_LIVE 101
#define P_STATE_IDLE 102

#define ID_ANI_P 21113

class CP :public CGameObject {
protected:
	float ax;
	float ay;


public:
	CP(float x, float y) : CGameObject(x, y) {
		this->ax = 0;
		this->ay = 0;
		vx = 0;
		vy = 0;
		SetState(P_STATE_IDLE);
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void OnNoCollision(DWORD dt);


	virtual int IsSpecial() { return 0; }
	virtual void SetState(int state);
};

