#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Cloud.h"

#include "Koopas.h"


class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					
	LPGAMEOBJECT hudp;
	LPGAMEOBJECT p;


	vector<LPGAMEOBJECT> huda;


	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> shinebricks;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }
	LPGAMEOBJECT GetHudP() { return hudp; }
	LPGAMEOBJECT GetP() { return p; }

	void Clear();


	void PurgeDeletedObjects();

	void HandleShineBrick();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);

	static bool ShineBrickDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

