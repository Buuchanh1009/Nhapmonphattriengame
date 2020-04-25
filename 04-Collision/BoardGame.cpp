#include "BoardGame.h"
#include "LoadResource.h"
#include "MathHelper.h"
#include "Camera.h"
#include "Game.h"
#include "Sprites.h"
#include "Skill.h"
#include "Simon.h"

CBoardGame::CBoardGame()
{
	CLoadResourcesHelper::LoadSprites("data\\boardgame\\boardgame_sprites.txt");
	CLoadResourcesHelper::LoadAnimations("data\\boardgame\\boardgame_anis.txt", this);
	time = 300;
	countdownTime = 0;
	hp = 16;
	
}

void CBoardGame::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CSimon* simon = CSimon::GetInstance();
	if (simon->get_isPick()) countdownTime = GetTickCount();
	if (simon->get_isPauseTime()) return;

	if (GetTickCount() - countdownTime >= 1000)
	{
		countdownTime = GetTickCount();
		time--;
	}
}

void CBoardGame::Render()
{
	CSprites *sprites = CSprites::GetInstance();
	x = CGame::GetInstance()->getCamPos_x();
	y = 0;
	animations[0]->Render(x, y);

	updateItemKill();
	updateScore();
	updateTime();
	updateStage();
	updateSkill();
	updateLife();
	updateHP();
}

void CBoardGame::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

}

void CBoardGame::updateItemKill()
{
	int skill = CSkill::GetInstance()->state;

	switch (skill)
	{
	case STATE_KNIFE:
		idSkill = SKILL_KNIFE;
		ax = 155;
		ay = 20;
		break;
	case STATE_HOLY_WATER:
		idSkill = SKILL_WATER;
		ax = 156.5f;
		ay = 17;
		break;
	case STATE_TOPWATCH:
		idSkill = SKILL_STOP;
		ax = 155;
		ay = 17;
		break;
	case STATE_ACE:
		idSkill = SKILL_AXE;
		ax = 155;
		ay = 17;
		break;
	case STATE_HIDDEN:
		idSkill = SKILL_HIDDEN;
		break;
	}

	CSprites *sprites = CSprites::GetInstance();

	sprites->Get(idSkill)->Draw(x + ax, ay);
}

void CBoardGame::updateScore()
{
	score = CSimon::GetInstance()->getScoreNum();
	CSprites *sprites = CSprites::GetInstance();
	vector<int> scores = CMathHelper::TachSo(score, 6);

	for (int i = 0; i < scores.size(); i++)
	{
		sprites->Get(9800 + scores[scores.size() - i - 1])->Draw(x + SCORE_X + i*6.5f, SCORE_Y);
	}
}

void CBoardGame::updateTime()
{
	CSprites *sprites = CSprites::GetInstance();
	vector<int> scores = CMathHelper::TachSo(time, 4);

	for (int i = 0; i < scores.size(); i++)
	{
		sprites->Get(9800 + scores[scores.size() - i - 1])->Draw(x + TIME_X + i * 7.5f, TIME_Y);
	}
}

void CBoardGame::updateStage()
{
	CSprites *sprites = CSprites::GetInstance();
	stage = CSimon::GetInstance()->det_stageNum();
	vector<int> scores = CMathHelper::TachSo(stage, 2);

	for (int i = 0; i < scores.size(); i++)
	{
		sprites->Get(9800 + scores[scores.size() - i - 1])->Draw(x + STAGE_X + i * 7.5f, STAGE_Y);
	}
}

void CBoardGame::updateLife()
{
	life = CSimon::GetInstance()->get_lifeNum();
	CSprites *sprites = CSprites::GetInstance();
	vector<int> scores = CMathHelper::TachSo(life, 2);

	for (int i = 0; i < scores.size(); i++)
	{
		sprites->Get(9800 + scores[scores.size() - i - 1])->Draw(x + LIFE_X + i * 7.5f, LIFE_Y);
	}
}

void CBoardGame::updateSkill()
{
	skill = CSimon::GetInstance()->get_skillNum();
	CSprites *sprites = CSprites::GetInstance();
	vector<int> scores = CMathHelper::TachSo(skill, 2);

	for (int i = 0; i < scores.size(); i++)
	{
		sprites->Get(9800 + scores[scores.size() - i - 1])->Draw(x + SKILL_X + i * 7.5f, SKILL_Y);
	}
}

void CBoardGame::updateHP()
{
	int hpSimon = CSimon::GetInstance()->get_HPNum() / 10;

	if (hp > hpSimon)
	{
		if (GetTickCount() - countdownHP >= COUNTDOWN_HP)
		{
			hp--;
			countdownHP = GetTickCount();
		}
	}
	else if (hp < hpSimon)
	{
		if (GetTickCount() - countdownHP >= COUNTDOWN_HP)
		{
			hp++;
			countdownHP = GetTickCount();
		}
	}

	CSprites *sprites = CSprites::GetInstance();
	vector<int> scores = CMathHelper::TachSo(skill, 2);

	for (int i = 0; i < 16; i++)
	{
		i < hp ? sprites->Get(9810)->Draw(x + HP_X + i*5, HP_Y) : sprites->Get(9811)->Draw(x + HP_X + i*5, HP_Y);
	}
}

CBoardGame* CBoardGame::__instance = NULL;
CBoardGame * CBoardGame::GetInstance()
{
	if (__instance == NULL) __instance = new CBoardGame();
	return __instance;
}