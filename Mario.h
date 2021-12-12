#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.08f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.65f
#define MARIO_JUMP_RUN_SPEED_Y	0.85f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_FALL_SLOWER 101
#define MARIO_STATE_FALL_SLOWER_RELEASE 102

#define MARIO_STATE_FLY_MAXSPEED 103
#define MARIO_STATE_FLY_MAXSPEED_RELEASE 104
#define MARIO_FLY_TIME 5000
#define MARIO_FLY_SPEED 0.03f;
#define MARIO_FLY_GRAVITY 0.00002f;

#define MARIO_STATE_ATTACK 105
#define MARIO_STATE_ATTACK_RELEASE 106


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601


// RACOON MARIO
#define ID_ANI_RACOON_IDLE_LEFT 1700
#define ID_ANI_RACOON_IDLE_RIGHT 1701

#define ID_ANI_RACOON_WALKING_LEFT 1800
#define ID_ANI_RACOON_WALKING_RIGHT 1801

#define ID_ANI_RACOON_RUNNING_LEFT 1900
#define ID_ANI_RACOON_RUNNING_RIGHT 1901

#define ID_ANI_RACOON_JUMP_WALK_LEFT 2000
#define ID_ANI_RACOON_JUMP_WALK_RIGHT 2001

#define ID_ANI_RACOON_JUMP_RUN_LEFT 2100
#define ID_ANI_RACOON_JUMP_RUN_RIGHT 2101

#define ID_ANI_RACOON_BRACE_RIGHT 2200
#define ID_ANI_RACOON_BRACE_LEFT 2201


#define ID_ANI_RACOON_SIT_RIGHT 2300
#define ID_ANI_RACOON_SIT_LEFT 2301

#define ID_ANI_RACOON_FALL_SLOWER_LEFT 2400
#define ID_ANI_RACOON_FALL_SLOWER_RIGHT 2401

#define ID_ANI_RACOON_ATTACK_LEFT 2500
#define ID_ANI_RACOON_ATTACK_RIGHT 2501


#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define	MARIO_LEVEL_RACOON	3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_RACOON_BBOX_WIDTH  14
#define MARIO_RACOON_BBOX_HEIGHT 24
#define MARIO_RACOON_SITTING_BBOX_WIDTH  14
#define MARIO_RACOON_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500

class CMario : public CGameObject
{

	vector<LPGAMEOBJECT> objects;
	CGameObject* obj = NULL;


	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int untouchable; 
	int life;
	int coinbounce;
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coin; 

	int flyable;
	BOOLEAN isMaxspeed;
	ULONGLONG fly_start;

	BOOLEAN isAttacking;

	BOOLEAN Holdable;
	BOOLEAN isHolding;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin2(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithBrickQuestion(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom2(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithPortalmini(LPCOLLISIONEVENT e);
	void OnCollisionWithP(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRacoon();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		coinbounce = 0;
		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		isMaxspeed = false;
		isAttacking = false;
		Holdable = false;
		isHolding = false;
		coin = 0;
		life = 1;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	int GetLevel() { return level; };
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void StartFly() { flyable = 1; fly_start = GetTickCount64(); /*DebugOut(L"============== OK !@#!@#!@#!@#\n");*/};
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};