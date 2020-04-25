#pragma once
#include "GameObject.h"

#define STATE_HIDDEN -1
#define STATE_ATTACK_RIGHT 0
#define STATE_ATTACK_LEFT	1

#define WEAPON_ANI_1_RIGHT	0
#define WEAPON_ANI_2_RIGHT	1
#define WEAPON_ANI_3_RIGHT	2

#define WEAPON_ANI_1_LEFT	3
#define WEAPON_ANI_2_LEFT	4
#define WEAPON_ANI_3_LEFT	5

#define WEAPON_BBOX_FRAME_1_WIDTH		9
#define WEAPON_BBOX_FRAME_1_HEIGHT		25
#define WEAPON_BBOX_FRAME_2_WIDTH		16
#define WEAPON_BBOX_FRAME_2_HEIGHT		20
#define WEAPON_BBOX_FRAME_3_WIDTH		27
#define WEAPON_BBOX_FRAME_3_HEIGHT		6
#define WEAPON_BBOX_FRAME_3_3_WIDTH		40
#define WEAPON_BBOX_FRAME_3_3_HEIGHT	6

class CWeapon : public CGameObject
{
	static CWeapon * __instance;
	int level;
	int frame;

	float xx, xy;
	bool isCol;
	DWORD action_time;
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> * colliable_objects = NULL);
	virtual void Render();
	void SetState(int statCSpritese);
	void SetPosTemp(float xx, float xy);
	void SetLevel(int level) { this->level = level; }
	void IncreaseLevel() {
		if (level < 3)
			level++;
	}

	void ResetAttack();
	void UpdatePositionWithSimon();
	
	int GetCurrentAnimation();

	CWeapon();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	static CWeapon * GetInstance();
};