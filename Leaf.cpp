#include "Leaf.h"


void CLeaf::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_LEAF)->Render(x, y);

	RenderBoundingBox();
}

void CLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CLeaf*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (vy < 0) vy += LEAF_BOUNCE_SPEED / 2;
	//if ((state == MUSHROOM_STATE_DIE) && (GetTickCount64() - die_start > MUSHROOM_DIE_TIMEOUT))
	//{
	//	isDeleted = true;
	//	return;
	//}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CLeaf::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LEAF_STATE_IDLE:
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case LEAF_STATE_BOUNCE:
		vy = -LEAF_BOUNCE_SPEED * 4;
		vx = 0.2f;
		ay = LEAF_GRAVITY;
		break;
	}

}