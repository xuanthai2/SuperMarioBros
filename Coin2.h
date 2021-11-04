#pragma once
#include "Coin.h"


#define ID_ANI_COIN 11000

#define	COIN2_WIDTH 8
#define COIN2_BBOX_WIDTH 8
#define COIN2_BBOX_HEIGHT 16
#define COIN2_STATE_LIVE 18
#define COIN2_STATE_DIE 19

#define COIN2_BOUNCE_SPEED 0.2f
#define COIN2_DIE_TIMEOUT 150


class CCoin2 :public CCoin {

	ULONGLONG die_start;

public:
		CCoin2(float x, float y) : CCoin(x, y) 
		{
			die_start = -1;
			SetState(COIN2_STATE_LIVE);
		}
		void Render();
		
		void SetState(int state);
		void GetBoundingBox(float& l, float& t, float& r, float& b);

		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
		virtual int IsCollidable() { return 1; };
		virtual int IsBlocking() { return 0; }
		
};

