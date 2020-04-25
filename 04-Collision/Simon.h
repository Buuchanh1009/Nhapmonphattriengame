#pragma once
#include "GameObject.h"
#include "LoadResource.h"

#define SIMON_WALKING_SPEED			0.05f
#define SIMON_GRAVITY				0.0005f
#define SIMON_JUMP_SPEED_Y			0.18f
#define SIMON_INJURE_X				0.4f
#define SIMON_INJURE_Y				0.01f
#define SIMON_AUTO_STAIR_SPEED		0.2f
#define SIMON_AUTO_STAIR_SPEED_Y	0.2f
#define SIMON_WALKING_SPEED_AUTO	0.018f
#define SIMON_WALKING_SPEED_MOVING	0.05f
#define SIMON_FLY_TIME				150

#define SIMON_HP_START				160

#define SIMON_STATE_IDLE			0
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
#define SIMON_STATE_SIT				500
#define SIMON_STATE_ATTACK			600
#define SIMON_STATE_PICK			700
#define SIMON_STATE_THROW			800
#define SIMON_STATE_UP_STAIR		900
#define SIMON_STATE_DOWN_STAIR		901

#define SIMON_ANI_IDLE_LEFT					0
#define SIMON_ANI_IDLE_RIGHT				1
#define SIMON_ANI_BACK						2
#define SIMON_ANI_INJURE_LEFT				3
#define SIMON_ANI_INJURE_RIGHT				4
#define SIMON_ANI_DIE_LEFT					5
#define SIMON_ANI_DIE_RIGHT					6
#define SIMON_ANI_WALKING_LEFT				7
#define SIMON_ANI_WALKING_RIGHT				8
#define SIMON_ANI_SIT_LEFT					9
#define SIMON_ANI_SIT_RIGHT					10
#define SIMON_ANI_ATTACK_LEFT				11
#define SIMON_ANI_ATTACK_RIGHT				12
#define SIMON_ANI_PICK_LEFT					13
#define SIMON_ANI_PICK_RIGHT				14
#define SIMON_ANI_SIT_ATTACK_LEFT			15
#define SIMON_ANI_SIT_ATTACK_RIGHT			16
#define SIMON_ANI_IDLE_UPSTAIR_RIGHT		17
#define SIMON_ANI_IDLE_DOWNSTAIR_RIGHT		18
#define SIMON_ANI_UPSTAIR_RIGHT				19
#define SIMON_ANI_DOWNSTAIR_RIGHT			20
#define SIMON_ANI_IDLE_UPSTAIR_LEFT			21
#define SIMON_ANI_IDLE_DOWNSTAIR_LEFT		22
#define SIMON_ANI_UPSTAIR_LEFT				23
#define SIMON_ANI_DOWNSTAIR_LEFT			24
#define SIMON_ANI_RIGHT_UP_ATTACK			25
#define SIMON_ANI_RIGHT_DOWN_ATTACK			26
#define SIMON_ANI_LEFT_DOWN_ATTACK			27
#define SIMON_ANI_LEFT_UP_ATTACK			28


#define SIMON_BBOX_WIDTH		17
#define SIMON_BBOX_HEIGHT		31
#define SIMON_SIT_BBOX_WIDTH	17
#define SIMON_SIT_BBOX_HEIGHT	24
#define SIMON_DIE_BBOX_WIDTH	17
#define SIMON_DIE_BBOX_HEIGHT	17
#define SIMON_RESET_BBOX		7

#define SIMON_ATTACK_TIME					400
#define SIMON_PICK_TIME						1600
#define SIMON_THROW_TIME					1000
#define SIMON_ENJURE_TIME					800
#define SIMON_UNTOUCHABLE_TIME				2500
#define CREATE_ENEMY_TIME					6000
#define SIMON_INVISIBLE_TIME				2000
#define SIMON_UNTOUCHABLE_INVISIBLE_TIME	5000
#define SIMON_DIE_TIME						3000
#define SIMON_HP_INJURE						20
#define INCREASE_SKILL_BIG					5
#define INCREASE_SKILL_SMALL				1

#define SIMON_DOWNSTAIR		-2
#define SIMON_UPSTAIR		2

class CSimon : public CGameObject
{
	static CSimon * __instance;

	//int hp;
	vector<int> skill;
	int life;
	int score;
	int stage;

	int sthrow;
	int alpha;

	int untouchable;
	DWORD untouchable_start;

	bool isBlock;
	bool isJump;
	bool isOnJump;
	bool jumpingMove;
	bool isAttack;
	bool isPick;
	bool isthrow;
	bool canStop;
	bool isSit;
	bool canSit;
	bool isInJure;
	bool isDie;
	bool isHasOtherStuff;
	bool isPausetime;
	bool isBeMoving;
	bool isInvisible;
	float be_x;
	int be_nx;
	int be_updown;
	int jump_nx;

	DWORD action_time;
	DWORD injure_time;
	DWORD invisible_time;
	DWORD untouchable_time;

public:

	CSimon();
	~CSimon() { ; };

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetHP(int h) { hp = h; }
	void SetIsBlock(bool block);
	void SetBeMoving(bool moving) { isBeMoving = moving; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	bool get_isBlock() { return isBlock; }
	bool get_isAttack() { return isAttack; }
	bool get_isJump() { return isJump; }
	bool get_isPick() { return isPick; }
	bool get_isThrow() { return isthrow; }
	bool get_isSit() { return isSit; }
	bool get_isInjure() { return isInJure; }
	int get_be_nx() { return be_nx; }
	int get_be_updown() { return be_updown; }
	int get_skillNum() { return skill[0]; }
	bool get_isBeMoving() { return isBeMoving; }
	bool get_canSit() { return canSit; }
	bool get_isOnJump() { return isOnJump; }
	

	void startAttack();
	void startJump();
	void startJumpMove(bool nxx);
	void startPick();
	void startThrow();
	void startSit(bool sit);
	void startInvisible();
	void resetSit();
	void upBBox();
	void beMoving(int bnx, float bx, int updown);
	void resetAttack();
	void resetDie();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	static CSimon * GetInstance();
};