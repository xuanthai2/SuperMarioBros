#pragma once
#include "Mushroom.h"

#define MUSHROOM2_GRAVITY 0.002f
#define MUSHROOM2_WALKING_SPEED 0.05f

#define ID_ANI_RED_MUSHROOM 12011
#define ID_ANI_GREEN_MUSHROOM 12012

#define MUSHROOM2_BBOX_WIDTH 16
#define MUSHROOM2_BBOX_HEIGHT 14
#define MUSHROOM2_BBOX_HEIGHT_DIE 7

#define MUSHROOM2_DIE_TIMEOUT 500

#define MUSHROOM2_STATE_WALKING 100
#define MUSHROOM2_STATE_DIE 200

//#define ID_ANI_MUSHROOM_WALKING 300

#define MUSHROOM_TYPE_RED 399
#define MUSHROOM_TYPE_GREEN 400

class CMushroom2 : public CMushroom
{
protected:
	float ax;
	float ay;

	float type;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();



	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CMushroom2(float x, float y, float type);
	virtual void SetState(int state);
	virtual float GetType() { return this->type; }
	virtual void SetType(float type) { this->type = type; }
};

