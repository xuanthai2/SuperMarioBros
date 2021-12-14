#include "HUD.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Textures.h"

void CHUD::Render()
{
	int aniID;
	if (type == HUD_TYPE_A)
	{
		if (state == HUD_STATE_OFF)
		{
			aniID = ID_ANI_HUD_ARROW_WHITE;
		}
		else
		{
			aniID = ID_ANI_HUD_ARROW_BLACK;
		}
	}
	else if (type == HUD_TYPE_P)
	{
		if (state == HUD_STATE_OFF)
		{
			aniID = ID_ANI_HUD_P_WHITE;
		}
		else
		{
			aniID = ID_ANI_HUD_P_BLACK;
		}
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniID)->Render(x, y);

	//RenderBoundingBox();
}

void CHUD::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - HUD_BBOX_WIDTH / 2;
	t = y - HUD_BBOX_HEIGHT / 2;
	r = l + HUD_BBOX_WIDTH;
	b = t + HUD_BBOX_HEIGHT;
}