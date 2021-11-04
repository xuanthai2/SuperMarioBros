#include "Coin2.h"

#include "Coin.h"

void CCoin2::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	RenderBoundingBox();
}

void CCoin2::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN2_BBOX_WIDTH / 2;
	t = y - COIN2_BBOX_HEIGHT / 2;
	r = l + COIN2_BBOX_WIDTH;
	b = t + COIN2_BBOX_HEIGHT;
}

void CCoin2::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case COIN2_STATE_LIVE:

		break;

	case COIN2_STATE_DIE:
		die_start = GetTickCount64();
		if (abs(this->vx) == 0) {
			vy = -COIN2_BOUNCE_SPEED * 3;
		}
		break;
	}
}

void CCoin2::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;
	if (vy < 0) vy += COIN2_BOUNCE_SPEED;
	if ((state == COIN2_STATE_DIE) && (GetTickCount64() - die_start > COIN2_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	//if (y >= vitricu)
	//{
	//	y = vitricu;
	//	vy = 0;
	//	return;
	//}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}