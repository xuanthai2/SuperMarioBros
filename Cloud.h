#pragma once
#include "GameObject.h"


#define ID_ANI_CLOUD 50000
#define	CLOUD_WIDTH 16
#define CLOUD_BBOX_WIDTH 10
#define CLOUD_BBOX_HEIGHT 16

class CCloud : public CGameObject {
protected:
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;

public:
	CCloud(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 1; }
	//virtual void DB(int& l, int& t, int& r, int& b) { l = 0; t = 1; r = 0; b = 0; }
	virtual int IsSpecial() { return 1; }
};

typedef CCloud* LPCLOUD;

