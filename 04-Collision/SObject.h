#pragma once
#include "GameObject.h"

#define SOBJECT_GRAVITY			0.00008f
#define SMALL_HEART_GRAVITY		0.00015f
#define MONEY_ACTIVE_SPEED		0.000095f

#define SOBJECT_HIDDEN				-1
#define SMALL_CANDLE				0
#define BIG_CANDLE					1
#define HEART_ITEM					2
#define CANE_ITEM					3
#define KNIFE_ITEM					4
#define MONEY_ITEM_1k				5
#define HEART_SMALL_ITEM			6
#define HOLY_WATER_ITEM				7
#define MONEY_ITEM_100				8
#define STOPWATCH_ITEM				9
#define CROSS_ITEM					10
#define STATE_WALL_1				11
#define STATE_BLACK					12
#define POT_ROAST_ITEM				13
#define STATE_WALL_2				14
#define STATE_WALL_3				15
#define AXE_ITEM					16
#define MONEY_ITEM_400				17
#define MONEY_ITEM_700				18
#define STATE_CRYSTAL				19
#define OTHER_STUFF_1				20
#define STATE_INVINCIBILITY_POTION	21

#define SOBJECT_APPEAR_TIME		5000
#define SOBJECT_DESTROY_TIME	500
#define SMALL_HEART_X_TIME		250

#define BBOX_BIG_CANDLE_W	16
#define BBOX_BIG_CANDLE_H	32

#define BBOX_SMALL_CANDLE_W		8
#define BBOX_SMALL_CANDLE_H		16

#define BBOX_HEART_ITEM_W		16
#define BBOX_HEART_ITEM_H		16

#define BBOX_MONEY_1K_W		16
#define BBOX_MONEY_1K_H		15

#define	BBOX_CANE_ITEM_W		16
#define BBOX_CANE_ITEM_H		16

#define BBOX_KNIFE_ITEM_W		16
#define BBOX_KNIFE_ITEM_H		9

#define BBOX_HEART_SMALL_W		6
#define BBOX_HEART_SMALL_H		11

#define HOLY_WATER_WIDTH	16
#define HOLY_WATER_HEIGHT	16

#define STOPWATCH_WIDTH		17
#define STOPWATCH_HEIGHT	17

#define CROSS_WIDTH			17
#define CROSS_HEIGHT		17

#define WALL_1_WIDTH		16
#define WALL_1_HEIGHT		14

#define AXE_WIDTH	16
#define AXE_HEIGHT	15

#define CRYSTAL_WIDTH	14
#define CRYSTAL_HEIGHT	16

#define OTHER_STUFF_1_WIDTH		14
#define OTHER_STUFF_1_HEIGHT	14

#define INVINCIBILITY_POTION_WIDTH	15
#define INVINCIBILITY_POTION_HEIGHT	18

class CSObject : public CGameObject
{
	int xAppear;
	bool isAppear;
	DWORD appear_start;

	bool isDestroy;
	DWORD destroy_start;

public :
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render();

	void ItemStart();
	virtual void BeDestroy();
	void SetxAppear(int x) { xAppear = x; }

	CSObject();
	~CSObject() {};
};