#pragma once
#include "GameObject.h"

#define EFFECT_GRAVITY			0.0001f

#define STATE_HIDDEN -1
#define STATE_DESTROY			0
#define STATE_BREAKING_WALL		1
#define STATE_SPLASH			2
#define STATE_MONEY_100			3
#define STATE_MONEY_400			4
#define STATE_MONEY_700			5
#define STATE_MONEY_1K			6
#define STATE_BOSS_1_DIE		7
#define STATE_WHITE				8
#define STATE_BE_HIT			9

#define DESTROY_EFFECT_WIDTH	8
#define DESTROY_EFFECT_HEIGHT	16
#define MONEY_WIDTH				40
#define MONEY_HEIGHT			18

#define DESTROY_EFFECT_TIME		400
#define BE_HIT_TIME				50

class CEffect : public CGameObject
{
	bool isShow;
	DWORD start_show;
	DWORD timeE;
	int alpha;

	int item;
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> * colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void StartShowEffect();
	void StartShowEffect(int item);
	void StartShowEffect(float vxx, float vyy);

	CEffect();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};