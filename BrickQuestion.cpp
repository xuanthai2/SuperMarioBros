#include "BrickQuestion.h"
#include "Coin.h"
#include "debug.h"

CBrickQuestion::CBrickQuestion(float x, float y, float inside) :CGameObject(x, y)
{
	this->inside = inside;
	
	SetState(BRICKQUESTION_LIVE);
}

void CBrickQuestion::Render()
{

	int aniId = ID_ANI_BRICKQUESTION;
	if (state == BRICKQUESTION_DIE) {
		aniId = ID_ANI_BRICKQUESTION_DIE;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	RenderBoundingBox();
}

void CBrickQuestion::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

//void CBrickQuestion::OnCollisionWith(LPCOLLISIONEVENT e)
//{
//	if (!e->obj->IsBlocking()) return;
//	if (dynamic_cast<CBrickQuestion*>(e->obj)) return;
//
//	if (e->ny != 0)
//	{
//		vy = 0;
//	}
//	else if (e->nx != 0)
//	{
//		vx = -vx;
//	}
//}
void CBrickQuestion::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICKQUESTION_DIE:
			//vy = -BRICK_BOUNCE_SPEED;
		break;
	case BRICKQUESTION_LIVE:
		
		break;
	}
}

void CBrickQuestion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//y += vy * dt;
	//if(vy < 0) {
	//	vy += BRICK_BOUNCE_SPEED / 4;
	//	if (y > vitricu) { 
	//		y = vitricu;
	//		vy = 0;
	//	}
	//	if (y >= vitricu)
	//	{
	//		y = vitricu;
	//		return;
	//	}
	//}



	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);


}