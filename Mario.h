#pragma once

#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#define MARIO_WIDTH 14

class CBrick : public CGameObject {
public: 
	CBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
};
class CCoin : public CGameObject {
public:
	CCoin(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
};
class CCloud : public CGameObject {
public:
	CCloud(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
};
class CCloud2 : public CGameObject {
public:
	CCloud2(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
};
class CCloud3 : public CGameObject {
public:
	CCloud3(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
};
class CNormalBrick : public CGameObject {
public:
	CNormalBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
};

class CMario : public CGameObject
{
protected:
	float vx;
public:
	CMario(float x, float y, float vx);
	void Update(DWORD dt);
	void Render();
};

class CEnemy : public CGameObject
{
protected:
	float vx;
public:
	CEnemy(float x, float y, float vx);
	void Update(DWORD dt);
	void Render();
};


