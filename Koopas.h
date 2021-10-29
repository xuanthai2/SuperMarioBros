#pragma once
#include "GameObject.h"

#define KOOPAS_GRAVITY 0.002f
#define KOOPAS_WALKING_SPEED 0.05f
#define KOOPAS_HIT_SPEED 0.2f


#define KOOPAS_BBOX_WIDTH 17
#define KOOPAS_BBOX_HEIGHT 24
#define KOOPAS_BBOX_HEIGHT_DIE 14

#define KOOPAS_DIE_TIMEOUT 500

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DIE 200
#define KOOPAS_STATE_HIT 300

#define ID_ANI_KOOPAS_WALKING 6000
#define ID_ANI_KOOPAS_DIE 6001
#define ID_ANI_KOOPAS_HIT 6002

class CKoopas : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CKoopas(float x, float y);
	virtual void SetState(int state);
};