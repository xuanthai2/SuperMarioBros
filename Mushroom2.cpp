#include "Mushroom2.h"



void CMushroom2::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM2_BBOX_WIDTH / 2;
	top = y - MUSHROOM2_BBOX_HEIGHT / 2;
	right = left + MUSHROOM2_BBOX_WIDTH;
	bottom = top + MUSHROOM2_BBOX_HEIGHT;

}

void CMushroom2::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMushroom2::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CMushroom2*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}


void CMushroom2::Render()
{
	int aniId;

	if (GetType() == MUSHROOM_TYPE_GREEN)
	{
		aniId = ID_ANI_GREEN_MUSHROOM;
	}
	else {
		aniId = ID_ANI_RED_MUSHROOM;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CMushroom2::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (vy < 0) vy += MUSHROOM2_BOUNCE_SPEED / 2;
	//if ((state == MUSHROOM_STATE_DIE) && (GetTickCount64() - die_start > MUSHROOM_DIE_TIMEOUT))
	//{
	//	isDeleted = true;
	//	return;
	//}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CMushroom2::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{

	case MUSHROOM2_STATE_IDLE:
		vx = 0;
		vy = 0;
		ay = 0;

		break;
	case MUSHROOM2_STATE_DIE:
		//die_start = GetTickCount64();
		//y += (MUSHROOM_BBOX_HEIGHT - MUSHROOM_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case MUSHROOM2_STATE_WALKING:
		vx = +MUSHROOM2_WALKING_SPEED;
		vy = -MUSHROOM2_BOUNCE_SPEED*4;
		ay = MUSHROOM2_GRAVITY;
		break;
	}

}