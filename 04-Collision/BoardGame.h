#pragma once
#include<iostream>
#include <vector>
#include "GameObject.h"
using namespace std;

#define SKILL_KNIFE		91041
#define SKILL_WATER		91061 
#define SKILL_STOP		91071 
#define SKILL_AXE		91078 
#define SKILL_HIDDEN	99999

#define SCORE_X			55
#define SCORE_Y			7

#define TIME_X			155
#define TIME_Y			7

#define STAGE_X			240
#define STAGE_Y			7

#define SKILL_X			200
#define SKILL_Y			17

#define LIFE_X			200
#define LIFE_Y			25

#define HP_X			60
#define HP_Y			17

#define COUNTDOWN_HP	200

class CBoardGame : public CGameObject
{
	static CBoardGame* __instance;

	int idSkill;
	float ax;
	float ay;

	int score;
	int time;
	int stage;
	int skill;
	int life;
	int hp;
	bool isPauseTime;

	DWORD countdownTime;
	DWORD countdownHP;
public:
	CBoardGame();
	~CBoardGame() { ; }
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> * colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	void updateItemKill();
	void updateScore();
	void updateTime();
	void updateStage();
	void updateSkill();
	void updateLife();
	void updateHP();
	void set_isPauseTime(bool pause) { isPauseTime = pause; }

	void resetTime() { time = 300; }
	void setSkill(int num) { skill += num; }
	void setStage(int t) { stage = t; }
	void setLife(int num) { life += num; }

	static CBoardGame* GetInstance();
};