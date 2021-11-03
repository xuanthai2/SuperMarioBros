#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f

#define GOOMBA_BOUNCE_SPEED  0.8f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7
#define GOOMBAFLY_BBOX_WIDTH 16
#define GOOMBAFLY_BBOX_HEIGHT 22
#define GOOMBAFLY_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100

#define GOOMBA_STATE_CANTFLY 302
#define GOOMBA_STATE_FLYING 301

#define GOOMBA_STATE_DIE 200

#define GOOMBA_STATE_BOUNCE 300

#define GOOMBA_TYPE_NORMAL 355
#define GOOMBA_TYPE_FLY 356

#define ID_ANI_GOOMBA_FLYING 5002
#define ID_ANI_GOOMBA_CANTFLY 5003

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001

class CGoomba : public CGameObject
{
protected:
	//float maxVx;
	float ax;				
	float ay; 
	float type;
	float oldvx;
	//BOOLEAN isOnPlatform;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public: 	
	CGoomba(float x, float y, float type);
	virtual void SetState(int state);
	virtual float GetType() { return this->type; }
	virtual void SetType(float type) { this->type = type; }
};