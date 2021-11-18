#pragma once
#include "GameObject.h"

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_WALKING_SPEED 0.05f

#define ID_ANI_RED_MUSHROOM 12011
#define ID_ANI_GREEN_MUSHROOM 12012

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 14
#define MUSHROOM_BBOX_HEIGHT_DIE 7

#define MUSHROOM_DIE_TIMEOUT 500

#define MUSHROOM_STATE_WALKING 100
#define MUSHROOM_STATE_DIE 200

//#define ID_ANI_MUSHROOM_WALKING 300

#define MUSHROOM_TYPE_RED 399
#define MUSHROOM_TYPE_GREEN 400




class CMushroom : public CGameObject
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
	CMushroom(float x, float y, float type) :CGameObject(x, y)
	{
		this->type = type;
		this->ax = 0;
		this->ay = MUSHROOM_GRAVITY;
		//die_start = -1;
		SetState(MUSHROOM_STATE_WALKING);
	}
	virtual void SetState(int state);
	virtual int GetType() { return this->type; }
	virtual void SetType(int type) { this->type = type; }
};

