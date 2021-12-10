#pragma once
#include "Coin.h"


#define ID_ANI_COIN 11000

#define	COIN2_WIDTH 8
#define COIN2_BBOX_WIDTH 16
#define COIN2_BBOX_HEIGHT 16
#define COIN2_STATE_LIVE 18
#define COIN2_STATE_DIE 19

#define COIN2_TYPE_ONCE 20
#define COIN2_TYPE_MULTI 21

#define COIN2_BOUNCE_SPEED 0.2f
#define COIN2_DIE_TIMEOUT 150


class CCoin2 :public CCoin {
	int timebounce;
	int type;
	float vitricu;
	ULONGLONG die_start;

public:
		CCoin2(float x, float y, int timebounce) : CCoin(x, y) 
		{
			this->vitricu = y;
			die_start = -1;
			if (timebounce == 0) {
				SetType(COIN2_TYPE_ONCE);
			}
			else if (timebounce == 5)
			{
				SetType(COIN2_TYPE_MULTI);
			}
			SetState(COIN2_STATE_LIVE);
		}
		void Render();
		
		void SetState(int state);
		void GetBoundingBox(float& l, float& t, float& r, float& b);
		void SetTB(int timebounce) { this->timebounce = timebounce; }
		int GetTB() { return timebounce = this->timebounce; }
		void SetType(int type) { this->type = type; }
		int GetType() { return type = this->type; }
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
		virtual int IsCollidable() { return 1; };
		virtual int IsBlocking() { return 0; }
		
};

