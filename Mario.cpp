#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"

#include "Coin.h"
#include "Coin2.h"

#include "Portal.h"

#include "Collision.h"

#include "BrickQuestion.h"
#include "Koopas.h"

#include "Mushroom.h"
#include "Mushroom2.h"

#include "Leaf.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	DebugOut(L"============== %d \n", (int)y);
	if (abs(vx) > abs(maxVx))
	{
		vx = maxVx;
		isMaxspeed = true;

	}
	if (GetTickCount64() - fly_start > MARIO_FLY_TIME)
	{
		fly_start = 0;
		flyable = 0;
		ay = MARIO_GRAVITY;
	}
	if(isOnPlatform) 	ay = MARIO_GRAVITY;
	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
		
	}
	isMaxspeed = false;
	isOnPlatform = false;


	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CMushroom2*>(e->obj))
		OnCollisionWithMushroom2(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CCoin2*>(e->obj))
		OnCollisionWithCoin2(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CBrickQuestion*>(e->obj))
		OnCollisionWithBrickQuestion(e);

}

void CMario::OnCollisionWithCoin2(LPCOLLISIONEVENT e)
{
	CCoin2* coin2 = dynamic_cast<CCoin2*>(e->obj);
	
	if (e->ny > 0) {
		if (coin2->GetType() == COIN2_TYPE_MULTI)
		{
			coinbounce++;
			coin2->SetTB(coinbounce);
			coin2->SetState(COIN2_STATE_DIE);
		}
		if (coin2->GetType() == COIN2_TYPE_ONCE)
		{
			coin2->SetState(COIN2_STATE_DIE);
		}
		coin++;
	
	}

}

void CMario::OnCollisionWithBrickQuestion(LPCOLLISIONEVENT e)
{
	CBrickQuestion* brickquestion = dynamic_cast<CBrickQuestion*>(e->obj);
	// jump on top >> kill Goomba and deflect a bit  -> now jump from below >> take poin
	if (e->ny > 0)
	{
			if (brickquestion->GetState() != BRICKQUESTION_DIE)
			{
				//float xx, yy;
				//brickquestion->GetPosition(xx, yy);
				DebugOut(L"============== BRICK INSIDE : %d \n", brickquestion->GetInside());
				//if (brickquestion->GetInside() == BRICK_INSIDE_COIN) {
				//	obj = new CCoin(xx, yy);
				//	obj->SetPosition(xx, yy);
				//	objects.push_back(obj);
				//	for (int i = 0; i < objects.size(); i++) {
				//		DebugOut(L"============== This line has been made \n");
				//		objects[i]->Render();
				//	}
				//}

				brickquestion->SetState(BRICKQUESTION_DIE);
			}
		

	}
	
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	e->obj->Delete();

	//vy = -MARIO_JUMP_DEFLECT_SPEED/2;
	if (mushroom->GetType() != MUSHROOM_TYPE_RED) {
		if (level < MARIO_LEVEL_BIG)
		{
			SetLevel(MARIO_LEVEL_BIG);
			life++;
		}
	}
	else if (mushroom->GetType() != MUSHROOM_TYPE_GREEN) {
		SetLevel(MARIO_LEVEL_BIG);
	}
}

void CMario::OnCollisionWithMushroom2(LPCOLLISIONEVENT e)
{
	CMushroom2* mushroom2 = dynamic_cast<CMushroom2*>(e->obj);
	if (e->ny > 0) {
		if (mushroom2->GetState() != MUSHROOM2_STATE_WALKING && mushroom2->GetState() != MUSHROOM2_STATE_DIE)
		{
			mushroom2->SetState(MUSHROOM2_STATE_WALKING);
		}
		else
		{
			if (mushroom2->GetState() == MUSHROOM2_STATE_WALKING)
			{


				e->obj->Delete();
				DebugOut(L"============== MUSHROOM TYPE : %d \n", mushroom2->GetType());

				//vy = -MARIO_JUMP_DEFLECT_SPEED/2;
				if (mushroom2->GetType() != MUSHROOM_TYPE_RED) {
					if (level < MARIO_LEVEL_BIG)
					{
						SetLevel(MARIO_LEVEL_BIG);
						life++;
					}
				}
				else if (mushroom2->GetType() != MUSHROOM_TYPE_GREEN) {
					SetLevel(MARIO_LEVEL_BIG);
				}
			}
		}
	}
	else
	{
		e->obj->Delete();
		DebugOut(L"============== MUSHROOM TYPE : %d \n", mushroom2->GetType());

		//vy = -MARIO_JUMP_DEFLECT_SPEED/2;
		if (mushroom2->GetType() != MUSHROOM_TYPE_RED) {
			if (level < MARIO_LEVEL_BIG)
			{
				SetLevel(MARIO_LEVEL_BIG);
				life++;
			}
		}
		else if (mushroom2->GetType() != MUSHROOM_TYPE_GREEN) {
			SetLevel(MARIO_LEVEL_BIG);
		}
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetType() == GOOMBA_TYPE_NORMAL) 
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				goomba->SetState(GOOMBA_STATE_DIE);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
		else if (goomba->GetType() == GOOMBA_TYPE_FLY)
		{
			if (goomba->GetState() == GOOMBA_STATE_FLYING)
			{
				goomba->SetState(GOOMBA_STATE_WALKING);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
			else if (goomba->GetState() == GOOMBA_STATE_WALKING)
			{
				goomba->SetState(GOOMBA_STATE_DIE);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_BIG)
				{
					vy = -MARIO_JUMP_DEFLECT_SPEED / 2;
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level > MARIO_LEVEL_SMALL)
				{
					//vy = -MARIO_JUMP_DEFLECT_SPEED / 2;
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);

	// jump on top >> kill Koompas and deflect a bit 
	if (e->ny < 0)
	{
		if ((koopas->GetState() != KOOPAS_STATE_DIE) && (koopas->GetState() != KOOPAS_STATE_HIT))
		{
			koopas->SetState(KOOPAS_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopas->GetState() != KOOPAS_STATE_WALKING && (koopas->GetState() != KOOPAS_STATE_HIT))
		{
			//koopas->SetState(KOOPAS_STATE_HIT);
			//koopas->SetSpeed(-KOOPAS_HIT_SPEED, +0.2f);
			float kx, ky;
			koopas->GetPosition(kx, ky);
			if (x <= kx)
			{
				koopas->SetSpeed(KOOPAS_HIT_SPEED, 0.2f);
				koopas->SetState(KOOPAS_STATE_HIT);
			}
			if (x > kx)
			{
				koopas->SetSpeed(-KOOPAS_HIT_SPEED, +0.2f);
				koopas->SetState(KOOPAS_STATE_HIT);
			}
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopas->GetState() == KOOPAS_STATE_HIT)
		{
			koopas->SetState(KOOPAS_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopas->GetState() == KOOPAS_STATE_DIE)
		{
			//float kx, ky;
			//float vx, vy;
			//koopas->GetSpeed(vx, vy);
			//koopas->GetPosition(kx, ky);
			koopas->SetState(KOOPAS_STATE_HIT);
			vy = -MARIO_JUMP_DEFLECT_SPEED;

			//if (x >= kx)
			//{
			//	koopas->SetSpeed(-KOOPAS_HIT_SPEED, vy);
			//	vy = -MARIO_JUMP_DEFLECT_SPEED;
			//}
			//else
			//{
			//	koopas->SetSpeed(KOOPAS_HIT_SPEED, vy);
			//	vy = -MARIO_JUMP_DEFLECT_SPEED;
			//}
		}
		//if (koopas->GetState() != KOOPAS_STATE_HIT && koopas->GetState() != KOOPAS_STATE_WALKING)
		//{
		//	koopas->SetState(KOOPAS_STATE_HIT);
		//	vy = -MARIO_JUMP_DEFLECT_SPEED;
		//}
		//else
		//{
		//	koopas->SetState(KOOPAS_STATE_HIT);
		//	vy = -MARIO_JUMP_DEFLECT_SPEED;
		//}

	}
	else // hit by Koompas
	{
		if (untouchable == 0)
		{
			if (koopas->GetState() != KOOPAS_STATE_DIE)
			{
				if (level > MARIO_LEVEL_BIG)
				{
					vy = -MARIO_JUMP_DEFLECT_SPEED / 2;
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level > MARIO_LEVEL_SMALL)
				{
					//vy = -MARIO_JUMP_DEFLECT_SPEED / 2;
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
			if (koopas->GetState() == KOOPAS_STATE_DIE)
			{
				float kx, ky;
				koopas->GetPosition(kx, ky);
				if (x < kx)
				{
					koopas->SetSpeed(KOOPAS_HIT_SPEED,0.2f);
					koopas->SetState(KOOPAS_STATE_HIT);
				}
				if (x > kx)
				{
					koopas->SetSpeed(-KOOPAS_HIT_SPEED, +0.2f);
					koopas->SetState(KOOPAS_STATE_HIT);
				}

			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	//CCoin* coin = dynamic_cast<CCoin*>(e->obj);
	//if (e->ny > 0) {
	//	if (coin->GetState() != COIN_STATE_DIE)
	//	{
	//		coin->SetState(COIN_STATE_DIE);
	//		e->obj->Delete();
	//	}
	//	coin++;
	//}
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);
	if (e->ny > 0) {
		if (leaf->GetState() != LEAF_STATE_BOUNCE)
		{
			leaf->SetState(LEAF_STATE_BOUNCE);
		}
		else {
		
			if (leaf->GetState() == LEAF_STATE_BOUNCE)
			{
			
				e->obj->Delete();
				if (level != MARIO_LEVEL_RACOON && level != MARIO_LEVEL_BIG)
				{
				
					SetLevel(MARIO_LEVEL_BIG);
					vy = -MARIO_JUMP_DEFLECT_SPEED;
				}
				else if (level != MARIO_LEVEL_RACOON && level != MARIO_LEVEL_SMALL)
				{
					SetLevel(MARIO_LEVEL_RACOON);
				}
			}
		}
	}
	else
	{
		if (leaf->GetState() == LEAF_STATE_BOUNCE)
		{
	
			e->obj->Delete();
			if (level != MARIO_LEVEL_RACOON && level != MARIO_LEVEL_BIG)
			{
		
				SetLevel(MARIO_LEVEL_BIG);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
		
			}
			else if (level != MARIO_LEVEL_RACOON && level != MARIO_LEVEL_SMALL)
			{
				SetLevel(MARIO_LEVEL_RACOON);
				vy = -MARIO_JUMP_DEFLECT_SPEED / 2;
			}
		}
	}


}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdRacoon()
{
	int aniId = -1;
	//if (state == MARIO_STATE_FALL_SLOWER)
	//{
	//	if (vx < 0)
	//	{
	//		aniId = ID_ANI_RACOON_FALL_SLOWER_LEFT;
	//	}
	//	else {
	//		aniId = ID_ANI_RACOON_FALL_SLOWER_RIGHT;
	//	}
	//}
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
			{
				aniId = ID_ANI_RACOON_JUMP_RUN_RIGHT;
				if (ay < MARIO_GRAVITY)
				{
					aniId = ID_ANI_RACOON_FALL_SLOWER_RIGHT;
				}
			}
			else {
				aniId = ID_ANI_RACOON_JUMP_RUN_LEFT;
				if (ay < MARIO_GRAVITY)
				{
					aniId = ID_ANI_RACOON_FALL_SLOWER_LEFT;
				}
			}
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_RACOON_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_RACOON_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_RACOON_SIT_LEFT;
			else
				aniId = ID_ANI_RACOON_SIT_RIGHT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_RACOON_IDLE_RIGHT;
				else aniId = ID_ANI_RACOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_RACOON_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_RACOON_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_RACOON_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_RACOON_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_RACOON_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_RACOON_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_RACOON_IDLE_RIGHT;

	return aniId;
}


void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_RACOON)
		aniId = GetAniIdRacoon();
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();


	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();

	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{


	case MARIO_STATE_FALL_SLOWER:
		if (isSitting) break;
		if (!isOnPlatform)
		{
			ay = MARIO_GRAVITY / 20;
		}
		break;
	case MARIO_STATE_FALL_SLOWER_RELEASE:
		if (isSitting) break;
		//if (!isOnPlatform)
		//{
			ay = MARIO_GRAVITY;
		//}
		break;
	case MARIO_STATE_FLY_MAXSPEED:
		if (isSitting) break;
		if (level != MARIO_LEVEL_RACOON) break;
		if (!isOnPlatform)
		{

			if (flyable==1)
			{
				ay = MARIO_FLY_GRAVITY;
				vy -= MARIO_FLY_SPEED;
			}
		}
		break;
	case MARIO_STATE_FLY_MAXSPEED_RELEASE:
		if (isSitting) break;
		if (level != MARIO_LEVEL_RACOON) break;
		if (!isOnPlatform)
		{

			if (flyable == 1)
			{
				ay = 0.0003f;
			}
		}
		break;








	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
			{
				vy = -MARIO_JUMP_RUN_SPEED_Y;
				if (level == MARIO_LEVEL_RACOON)
				{
					StartFly();
				}
			}
			
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}

	else if (level == MARIO_LEVEL_RACOON)
	{
		if (isSitting)
		{
			left = x - MARIO_RACOON_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_RACOON_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_RACOON_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_RACOON_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_RACOON_BBOX_WIDTH / 2;
			top = y - MARIO_RACOON_BBOX_HEIGHT / 2;
			right = left + MARIO_RACOON_BBOX_WIDTH;
			bottom = top + MARIO_RACOON_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
		//y -= 30;
	}
	level = l;
}

