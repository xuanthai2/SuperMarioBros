#include "P.h"
void CP::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_P)->Render(x, y);

	//RenderBoundingBox();
}

void CP::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - P_BBOX_WIDTH / 2;
	t = y - P_BBOX_HEIGHT / 2;
	r = l + P_BBOX_WIDTH;
	b = t + P_BBOX_HEIGHT;
}

void CP::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (vy < 0) vy += 0.2f / 8;



	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CP::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CP::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case P_STATE_IDLE:
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case P_STATE_LIVE:
		vy = -0.2;
		ay = LEAF_GRAVITY / 3;
		break;
	}
}
