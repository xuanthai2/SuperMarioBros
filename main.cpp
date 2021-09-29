/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 02 - SPRITE AND ANIMATION

	This sample illustrates how to:

		1/ Render a sprite (within a sprite sheet)
		2/ How to manage sprites/animations in a game
		3/ Enhance CGameObject with sprite animation
================================================================ */

#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include "debug.h"
#include "Game.h"
#include "Textures.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Animation.h"
#include "Animations.h"


#include "Mario.h"


#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"
#define WINDOW_ICON_PATH L"mario.ico"

#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255,0.0f)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20

#define TEXTURES_DIR L"textures"
#define TEXTURE_PATH_MARIO TEXTURES_DIR "\\mario.png"
#define TEXTURE_PATH_MISC TEXTURES_DIR "\\misc.png"
#define TEXTURE_PATH_ENEMIES TEXTURES_DIR "\\enemies.png"

CMario *mario;
#define MARIO_START_X 10.0f
#define MARIO_START_Y 130.0f
#define MARIO_START_VX 0.1f

CBrick *brick;
CNormalBrick* NormalBrick;
#define BRICK_X 10.0f;
#define BRICK_Y 120.0f;
#define BRICK_WIDTH 16.0f;
#define BRICK_HEIGHT 16.0f;
CCloud* cloud;

C2nd *Cnd;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();
	
	textures->Add(ID_TEX_MARIO, TEXTURE_PATH_MARIO);
	//textures->Add(ID_ENEMY_TEXTURE, TEXTURE_PATH_ENEMIES, D3DCOLOR_XRGB(156, 219, 239));
	textures->Add(ID_TEX_MISC, TEXTURE_PATH_MISC);

	textures->Add(ID_TEX_ENEMY, TEXTURE_PATH_ENEMIES);


	CSprites * sprites = CSprites::GetInstance();
	
	LPTEXTURE texMario = textures->Get(ID_TEX_MARIO);

	// readline => id, left, top, right 

	sprites->Add(10001, 246, 154, 259, 181, texMario);
	sprites->Add(10002, 275, 154, 290, 181, texMario);
	sprites->Add(10003, 304, 154, 321, 181, texMario);

	sprites->Add(10011, 186, 154, 200, 181, texMario);
	sprites->Add(10012, 155, 154, 171, 181, texMario);
	sprites->Add(10013, 125, 154, 141, 181, texMario);

	LPTEXTURE texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(20001, 300, 117, 316, 133, texMisc);
	sprites->Add(20002, 318, 117, 334, 133, texMisc);
	sprites->Add(20003, 336, 117, 352, 133, texMisc);
	sprites->Add(20004, 354, 117, 370, 133, texMisc);


	LPTEXTURE texEnemies = textures->Get(ID_TEX_ENEMY);
	sprites->Add(300001,417,54,435,82,texEnemies);
	sprites->Add(300002, 435, 53, 454, 82, texEnemies);
	sprites->Add(300003, 456, 55, 473, 82, texEnemies);

	sprites->Add(300011, 456, 187, 476, 215, texEnemies);
	sprites->Add(300012, 437, 187, 457, 215, texEnemies);
	sprites->Add(300013, 418, 187, 437, 215, texEnemies);

	LPTEXTURE texNormalBrick = textures->Get(ID_TEX_MISC);
	sprites->Add(200001,299,134,317,152,texNormalBrick);
	sprites->Add(200002,317,134,335,152,texNormalBrick);
	sprites->Add(200003,335,134,353,152,texNormalBrick);
	sprites->Add(200004,353,134,371,152,texNormalBrick);
	sprites->Add(200005,371,134,389,152,texNormalBrick);

	LPTEXTURE texCloud = textures->Get(ID_TEX_MISC);
	sprites->Add(200011,389,116,407,132,texCloud);
	sprites->Add(200012,407,116,425,132,texCloud);
	sprites->Add(200013,425,116,444,132,texCloud);


	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(500, ani);

	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(501, ani);

	
	ani = new CAnimation(100);
	ani->Add(20001,1000);
	ani->Add(20002);
	ani->Add(20003);
	ani->Add(20004);
	animations->Add(510, ani);

	ani = new CAnimation(100);
	ani->Add(300011,100);
	ani->Add(300012);
	ani->Add(300013);
	animations->Add(512, ani);

	ani = new CAnimation(100);
	ani->Add(300001,100);
	ani->Add(300002);
	ani->Add(300003);
	animations->Add(511, ani);
	

	ani = new CAnimation(100);
	ani->Add(200001);
	//ani->Add(200002);
	//ani->Add(200003);
	//ani->Add(200004);
	//ani->Add(200005);
	animations->Add(509, ani);
	///
	ani = new CAnimation(100);
	ani->Add(200011);
	animations->Add(508, ani);
	///

	mario = new CMario(MARIO_START_X + 50.0f, MARIO_START_Y, MARIO_START_VX);
	brick = new CBrick(100.0f, 100.0f);
	Cnd = new C2nd(MARIO_START_X , MARIO_START_Y, MARIO_START_VX);
	cloud = new CCloud(50.0f,10.0f);

	//
	NormalBrick = new CNormalBrick(7.0f,150.0f);
	//
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	mario->Update(dt);
	Cnd->Update(dt);
}

void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	if (pD3DDevice != NULL)
	{
		// clear the background 
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

		// Use Alpha blending for transparent sprites
		FLOAT NewBlendFactor[4] = { 0,0,0,0 };
		pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

		brick->Render();
		mario->Render();
		Cnd->Render();

		//
		cloud->Render();

		//

		//
		float x = 9.0f;
		float y = 150.0f;
		for (int j = 0; j <= 3; j++) {
			for (int i = 0; i < 19; i++)
			{
				NormalBrick = new CNormalBrick(x, y);
				NormalBrick->Render();
				x = x + 16.0f;
			}
			x = 9.0f;
			y = y + 16.0f;
		}

		//
	

		// Uncomment this line to see how to draw a porttion of a texture  
		//g->Draw(10, 10, texMisc, 300, 117, 316, 133);


		spriteHandler->End();
		pSwapChain->Present(0, 0);
	}
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		DWORD ErrCode = GetLastError();
		DebugOut(L"[ERROR] CreateWindow failed! ErrCode: %d\nAt: %s %d \n", ErrCode, _W(__FILE__), __LINE__);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetDebugWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update((DWORD)dt);
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	CGame *game = CGame::GetInstance();
	game->Init(hWnd);

	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}