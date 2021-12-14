#pragma once

#include "GameObject.h"

#define ID_ANI_HUD_ARROW_WHITE 50002
#define ID_ANI_HUD_ARROW_BLACK 50003
#define ID_ANI_HUD_P_WHITE 50004
#define ID_ANI_HUD_P_BLACK 50005
#define	HUD_WIDTH 16
#define HUD_BBOX_WIDTH 15
#define HUD_BBOX_HEIGHT 6

#define HUD_TYPE_A 50006
#define HUD_TYPE_P 50007
#define HUD_STATE_ON 111
#define HUD_STATE_OFF 112


class CHUD : public CGameObject {
	int type;

public:
	CHUD(float x, float y, int type) : CGameObject(x, y) {
		this->type = type;
		state = HUD_STATE_OFF;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }

	int GetType() { return this->type; }
	void SetType(int type) { this->type = type; }
};

