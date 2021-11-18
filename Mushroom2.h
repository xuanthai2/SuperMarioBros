#pragma once
#include "Mushroom.h"

#define MUSHROOM2_GRAVITY 0.003f
#define MUSHROOM2_WALKING_SPEED 0.05f

#define ID_ANI_RED_MUSHROOM 12011
#define ID_ANI_GREEN_MUSHROOM 12012

#define MUSHROOM2_BBOX_WIDTH 14
#define MUSHROOM2_BBOX_HEIGHT 12
#define MUSHROOM2_BBOX_HEIGHT_DIE 7

#define MUSHROOM2_DIE_TIMEOUT 500

#define MUSHROOM2_STATE_WALKING 100
#define MUSHROOM2_STATE_DIE 200
#define MUSHROOM2_STATE_IDLE 62
#define MUSHROOM2_BOUNCE_SPEED 0.2f

//#define ID_ANI_MUSHROOM_WALKING 300

#define MUSHROOM_TYPE_RED 399
#define MUSHROOM_TYPE_GREEN 400

class CMushroom2 : public CMushroom
{
protected:
	float ax;
	float ay;

	int type;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();



	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CMushroom2(float x, float y, float type) : CMushroom(x, y, type) 
	{
		this->type = type;
		this->ax = 0;
		this->ay = 0;/*MUSHROOM_GRAVITY;*/
		//die_start = -1;
		vx = 0;
		vy = 0;
		SetState(MUSHROOM2_STATE_IDLE);
	}
	virtual void SetState(int state);
	virtual int GetType() { return this->type; }
	virtual void SetType(int type) { this->type = type; }
};

