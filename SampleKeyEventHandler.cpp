#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"


#include "HUD.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	CHUD* hud = (CHUD*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetHudP();
	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	//
	case DIK_X:
		if (mario->GetLevel() == MARIO_LEVEL_RACOON) {
			mario->SetState(MARIO_STATE_FALL_SLOWER);
		}
		break;
	case DIK_D:
		if (mario->GetLevel() == MARIO_LEVEL_RACOON)
		{
			mario->SetState(MARIO_STATE_FLY_MAXSPEED);

			hud->SetState(HUD_STATE_ON);
		}
		break;
	case DIK_Z:
		mario->SetState(MARIO_STATE_ATTACK);
		break;

	//
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_RACOON);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;	

	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_X:
		if (mario->GetLevel() == MARIO_LEVEL_RACOON) {
			mario->SetState(MARIO_STATE_FALL_SLOWER_RELEASE);
		}
		//mario->SetState(MARIO_STATE_FALL_SLOWER_RELEASE);
		break;
	case DIK_D:
		if (mario->GetLevel() == MARIO_LEVEL_RACOON)
		{
			mario->SetState(MARIO_STATE_FLY_MAXSPEED_RELEASE);
		}
		break;
	case DIK_Z:
		mario->SetState(MARIO_STATE_ATTACK_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CHUD* hud = (CHUD*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetHudP();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
			hud->SetState(HUD_STATE_ON);
		}
		else
		{
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
			hud->SetState(HUD_STATE_OFF);
		}
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
			hud->SetState(HUD_STATE_ON);
		}
		else
		{
			mario->SetState(MARIO_STATE_WALKING_LEFT);
			hud->SetState(HUD_STATE_OFF);
		}
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
		//hud->SetState(HUD_STATE_OFF);
}