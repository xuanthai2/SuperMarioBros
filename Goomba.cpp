#include "Goomba.h"
#include "Koopas.h"
#include "Collision.h"
#include "Platform.h"
#include "Cloud.h"
#include "debug.h"

CGoomba::CGoomba(float x, float y, float type) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	this->type = type;
	touchground = 0;
	die_start = -1;
	isOnPlatform = false;
	oldvx = -GOOMBA_WALKING_SPEED;

	//isOnPlatform = false;
	if (type == GOOMBA_TYPE_NORMAL) {
		SetState(GOOMBA_STATE_WALKING);
	}
	if (type == GOOMBA_TYPE_FLY) {

		SetState(GOOMBA_STATE_FLYING);
		
	}
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (GetType() == GOOMBA_TYPE_NORMAL) {
		if (state == GOOMBA_STATE_DIE)
		{
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
		}
		else
		{
			left = x  - GOOMBA_BBOX_WIDTH / 2;
			top = y  - GOOMBA_BBOX_HEIGHT / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT;
		}
	}
	if (GetType() == GOOMBA_TYPE_FLY) {
		if (state == GOOMBA_STATE_DIE)
		{
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
		}
		else if (state == GOOMBA_STATE_FLYING) 
		{
			left = x - GOOMBAFLY_BBOX_WIDTH / 2;
			top = y - GOOMBAFLY_BBOX_HEIGHT / 2;
			right = left + GOOMBAFLY_BBOX_WIDTH;
			bottom = top + GOOMBAFLY_BBOX_HEIGHT;
		}
		else if (state == GOOMBA_STATE_WALKING)
		{
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT;
		}
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CPlatform*>(e->obj))
	{
		OnCollisionWithPlatform(e);
	}
	if (dynamic_cast<CCloud*>(e->obj))
	{
		OnCollisionWithCloud(e);
	}
	if (dynamic_cast<CKoopas*>(e->obj))
	{
		OnCollisionWithKoopas(e);
	}
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 

	if (e->ny != 0 )
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
		//isOnPlatform = false;
	}
	
		
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
	vy += ay * dt;
	vx += ax * dt;
	oldvx = vx;
	if (vy < 0) vy += GOOMBA_BOUNCE_SPEED /4;
	//if (abs(vx) >= abs(maxVy)) vx = -maxVy;

	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}

	//if ((state == GOOMBA_STATE_FLYING) && (a > 0) && (a < 2) )
	//{
	//	//begin = GetTickCount64();
	//	vy = -GOOMBA_BOUNCE_SPEED;
	//}

	//if (GetTickCount64() - touchground > GOOMBA_FLY_TIMEOUT) {
	//	DebugOut(L"==============!@#!@#!@#  : %d \n", touchground);
	//}

	if ((state == GOOMBA_STATE_FLYING) && (GetTickCount64() - touchground > GOOMBA_FLY_TIMEOUT))
	{
		//DebugOut(L"============== y : %d \n", int(y));
		//if (int(y) <= yflying) {
		//	vy += GOOMBA_BOUNCE_SPEED / 8;
		//}
		//if (int(y) >= (ystanding)) {
		//	vy = -GOOMBA_BOUNCE_SPEED / 2;
		//}
		
		vy = -GOOMBA_BOUNCE_SPEED*2;
	}
	if (isOnPlatform && GetTickCount64() - touchground > GOOMBA_FLY_TIMEOUT) {
		touchground = GetTickCount64();
	}

	isOnPlatform = false;
	//if (vy < 0) vy += GOOMBA_BOUNCE_SPEED / 4 ;


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	//int aniId = ID_ANI_GOOMBA_WALKING;
	//if (state == GOOMBA_STATE_DIE) 
	//{
	//	aniId = ID_ANI_GOOMBA_DIE;
	//}
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (GetType() == GOOMBA_TYPE_FLY) {
		if (state == GOOMBA_STATE_FLYING) {
			aniId = ID_ANI_GOOMBA_FLYING;
		}
		else if (state == GOOMBA_STATE_WALKING) {
			aniId = ID_ANI_GOOMBA_WALKING;
		}
		else if (state == GOOMBA_STATE_DIE) {
			aniId = ID_ANI_GOOMBA_DIE;
		}
	}
	if (GetType() == GOOMBA_TYPE_NORMAL) {
		if (state == GOOMBA_STATE_WALKING) {
			aniId = ID_ANI_GOOMBA_WALKING;
		}
		else {
			aniId = ID_ANI_GOOMBA_DIE;
		}
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			break;
		case GOOMBA_STATE_WALKING: 
			vx = oldvx;
			break;
		case GOOMBA_STATE_FLYING:
			ay = GOOMBA_GRAVITY;
			vx = -GOOMBA_WALKING_SPEED;
			touchground = GetTickCount64();
			//this->ystanding = (int)y;
			//this->yflying = int(y) - 40;

			//vy = -GOOMBA_BOUNCE_SPEED / 2;

			//maxVy = abs(vy*4);
			break;
		case GOOMBA_STATE_BOUNCE:
			state == GOOMBA_STATE_DIE;
			vy = -GOOMBA_BOUNCE_SPEED * 2;
			break;
	}
}

void CGoomba::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);

	// jump on top >> kill Koompas and deflect a bit 
	if (e->ny < 0)
	{

	}
	else // hit by Koompas
	{

			if (koopas->GetState() != KOOPAS_STATE_DIE && koopas->GetState() != KOOPAS_STATE_WALKING )
			{
				//if (GetType() == GOOMBA_TYPE_NORMAL) {
					if (GetState() != GOOMBA_STATE_DIE) {
						SetState(GOOMBA_STATE_DIE);
						//if (abs(this->vx) == goomba_walking_speed)
						//	vy = -goomba_bounce_speed;
						//else
						//	vy = -goomba_bounce_speed;

					}
				//}
				//else {

				//}
			}
	}
}
void CGoomba::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	int xxx = x;
	//DebugOut(L"============== x : %d \n",xxx);
	//DebugOut(L"============== start : %d \n", platform->GetStart());
	//DebugOut(L"============== end : %d \n", platform->GetEnd());
	if (xxx >= platform->GetEnd())
	{
	vx = -GOOMBA_WALKING_SPEED;
	//x = x + 10;
	}
	if (xxx <= platform->GetStart())
	{
		vx = GOOMBA_WALKING_SPEED;
		//DebugOut(L"============== TUNR +++++ \n");
		//x = x + 10;
	}
}

void CGoomba::OnCollisionWithCloud(LPCOLLISIONEVENT e)
{
	CCloud* cloud = dynamic_cast<CCloud*>(e->obj);
	int xxx = x;
	//DebugOut(L"============== x : %d \n", xxx);
	//DebugOut(L"============== start : %d \n", cloud->GetStart());
	//DebugOut(L"============== end : %d \n", cloud->GetEnd());
	if (xxx >= cloud->GetEnd())
	{
		vx = -GOOMBA_WALKING_SPEED;
		//x = x + 10;
	}
	if (xxx <= cloud->GetStart())
	{
		vx = GOOMBA_WALKING_SPEED;
		//DebugOut(L"============== TUNR +++++ \n");
		//x = x + 10;
	}
}
