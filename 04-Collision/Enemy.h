#pragma once
#include "GameObject.h"


#define ENEMY_GRAVITY			0.0001f
#define JUMP_TIME_BEZIER		0.01f
#define SPACE_ERROR_MIN			20.0f
#define Y_MOVE_BEGIN			70.0f
#define Y_MOVE_END				120.0f

#define STATE_BOSS_1			5

#define ANI_BOSS_1_INACTIVE		18
#define ANI_BOSS_1_ACTIVE		19

#define GHOST_WIDTH				16
#define GHOST_HEIGHT			32
#define WOLF_WIDTH				32
#define WOLF_HEIGHT				16
#define BAT_WIDTH				17
#define BAT_HEIGHT				15
#define FISH_MONSTER_WIDTH		16
#define FISH_MONSTER_HEIGHT		31
#define BULLET_WIDTH			6
#define BULLET_HEIGHT			7
#define BOSS_1_WIDTH			48
#define BOSS_1_HEIGHT			23

#define ACTION_LEFT				-1
#define ACTION_RIGHT			1
#define HIT_HP					20
#define HP_DEFAULT				20
#define HP_BOSS					160
#define BOSS_BIHIT_TIME		    1000

class CEnemy : public CGameObject
{
	//int hp;
	int nxx;
	int move_time;

	float x_min;
	float x_max;
	float vyy;

	bool isFly;
	bool isFishMove;
	bool isShoot;
	bool splash;
	bool behit;
	DWORD behit_time;
	DWORD action_time;


	// boss


	bool isAttack;

	float xOld, yOld;	// vị trí cũ
	float xSimon, ySimon; // vị trí simon
	float xMove, yMove; // vị trí đến
	float bezier_time;

	bool waiting;
	bool moving_straight;
	bool moving_bezier;
	
	DWORD waiting_time;

public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render();
	virtual void SetState(int state);
	virtual void BeDestroy();

	int RandomItem();
	void be_hit();

	void boss_1_update();

	void boss_move_straight();
	void boss_move_bezier();

	bool onFlag();
	void setNxx(int xx) { nxx = xx; }
	void setActive(bool at) { isActive = at; }
	void SetMaxMin(float min, float max) { x_min = min; x_max = max; }
	CEnemy();
	~CEnemy() {};
};