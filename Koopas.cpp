#include "Koopas.h"

#include "Collision.h"
#include "debug.h"
#include "Platform.h"
#include "Cloud.h"
#include "BrickQuestion.h"

CKoopas::CKoopas(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	die_start = -1;
	SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if ((state == KOOPAS_STATE_DIE) || (state == KOOPAS_STATE_HIT))
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_DIE / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_DIE;
	}
	else if (state == KOOPAS_STATE_WALKING)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	if (state == KOOPAS_STATE_DIE)
	{
		x += vx * dt;
		y += vy * dt;
	}
	else if (state == KOOPAS_STATE_HIT)
	{
		x += vx * dt;
		y += vy * dt;
	}
	else if (state == KOOPAS_STATE_WALKING){ 
		x += vx * dt;
		y += vy * dt;
	}


}



void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopas*>(e->obj)) return;
	if (dynamic_cast<CCloud*>(e->obj))
	{
		OnCollisionWithCloud(e);
	}
	if (dynamic_cast<CPlatform*>(e->obj))
	{
		OnCollisionWithPlatform(e);
	}
	if (dynamic_cast<CBrickQuestion*>(e->obj))
	{
		OnCollisionWithQuestionBrick(e);
	}
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	//if ((state == KOOPAS_STATE_DIE) && (GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT))
	//{
	//	isDeleted = true;
	//	return;
	//}
	//if ((state == KOOPAS_STATE_HIT) && (GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT))
	//{
	//	isDeleted = true;
	//	return;
	//}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopas::Render()
{
	int aniId = ID_ANI_KOOPAS_WALKING_LEFT;
	if (vx < 0) {
		aniId = ID_ANI_KOOPAS_WALKING_LEFT;
	}
	else if (vx > 0) {
		aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
	}
	if (state == KOOPAS_STATE_DIE)
	{
		aniId = ID_ANI_KOOPAS_DIE;
	}
	else if(state == KOOPAS_STATE_HIT)
	{
		aniId = ID_ANI_KOOPAS_HIT;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}


void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE:
		//die_start = GetTickCount64();
		//y += (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ax = 0;
		break;
	case KOOPAS_STATE_WALKING:
		vx = -KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_HIT:
		//y += (KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE) / 2;
		//vx = -KOOPAS_HIT_SPEED;
		ax = 0;
		ay = KOOPAS_GRAVITY;
		break;
	}
}

void CKoopas::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	int xxx = x;
	if (state == KOOPAS_STATE_WALKING)
	{
		if (xxx >= platform->GetEnd())
		{
			vx = -KOOPAS_WALKING_SPEED;
			//x = x + 10;
		}
		if (xxx <= platform->GetStart())
		{
			vx = KOOPAS_WALKING_SPEED;
			//x = x + 10;
		}
	}
}

void CKoopas::OnCollisionWithCloud(LPCOLLISIONEVENT e)
{
	CCloud* cloud = dynamic_cast<CCloud*>(e->obj);
	int xxx = x;
	if (state == KOOPAS_STATE_WALKING)
	{
		if (xxx >= cloud->GetEnd())
		{
			vx = -KOOPAS_WALKING_SPEED;
			//x = x + 10;
		}
		if (xxx <= cloud->GetStart())
		{
			vx = KOOPAS_WALKING_SPEED;
			//x = x + 10;
		}
	}
}

void CKoopas::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	CBrickQuestion* brickquestion = dynamic_cast<CBrickQuestion*>(e->obj);
	if (state == KOOPAS_STATE_HIT)
	{
		if (brickquestion->GetState() != BRICKQUESTION_DIE)
		{
			brickquestion->SetState(BRICKQUESTION_DIE);
		}
	}
}




