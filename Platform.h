#pragma once

#include "GameObject.h"

// 
// The most popular type of object in Mario! 
// 
class CPlatform : public CGameObject
{
protected: 
	int length;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;
	int start;
	int end;

public: 
	CPlatform(float x, float y,
		float cell_width, float cell_height, int length,
		int sprite_id_begin, int sprite_id_middle, int sprite_id_end, int start, int end) :CGameObject(x, y)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = sprite_id_begin;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdEnd = sprite_id_end;
		this->start = start;
		this->end = end;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
	//virtual int IsCollidable() { return 0; }
	virtual int IsBlocking() { return 1; }
	virtual int IsSpecial() { return 0; }
	virtual int GetStart() { return this->start; }
	virtual int GetEnd() { return this->end; }

	virtual void SetStart(int start) { this->start = start; }
	virtual void SetEnd(int start) { this->end = end; }
};

typedef CPlatform* LPPLATFORM;