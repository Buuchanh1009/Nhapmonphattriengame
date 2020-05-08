#include <algorithm>
#include "debug.h"
#include <random>

#include "Simon.h"
#include "Ground.h"
#include "Game.h"
#include "Map.h"
#include "SObject.h"
#include "Weapon.h"
#include "Skill.h"
#include "LoadResource.h"
#include "Camera.h"


CSimon::CSimon()
{
	skill.push_back(5);
	alpha = 255;

	CLoadResourcesHelper::LoadSprites("data\\simon\\simon_sprites.txt");
	CLoadResourcesHelper::LoadAnimations("data\\simon\\simon_anis.txt", this);
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{

	CGameObject::Update(dt);

	if (isBlock && !isBeMoving)
	{
		SetState(SIMON_STATE_IDLE);
		return;
	}
	
	if (isBeMoving && !isBlock )
	{

		if (x - be_x > 0.5f)
		{
			vx = -SIMON_WALKING_SPEED_MOVING;
			nx = -1;
			state = SIMON_STATE_WALKING_LEFT;
		}
		else if (x - be_x < -0.5f)
		{
			vx = SIMON_WALKING_SPEED_MOVING;
			nx = 1;
			state = SIMON_STATE_WALKING_RIGHT;
		}
		
	}

	vy += SIMON_GRAVITY * dt;
	

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	CWeapon* weapon = CWeapon::GetInstance();
	CSkill* skill = CSkill::GetInstance();
	CMap* map = CMap::GetInstance();

	/*vector<LPGAMEOBJECT> coObjectFlag;
	coObjectFlag = map->Get_coObjectFlag();*/

	// pick
	if (GetTickCount() - action_time >= SIMON_PICK_TIME)
	{
		isPick = false;
		action_time = 0;
	}
	else if (isPick)
	{
		dx = 0;
	}

	if (isPick)
	{
		weapon->set_isHidden(true);
	}
	if (isSit) { dx = 0; }
	// attack
	if (GetTickCount() - action_time > SIMON_ATTACK_TIME)
	{
		isAttack = false;
		action_time = 0;
		weapon->SetPosTemp(x, y);
	}
	else if (isAttack)
	{
		weapon->SetPosTemp(x, y);
		if (!isJump && !isOnJump) dx = 0;
	}

	// throw
	if (GetTickCount() - action_time >= SIMON_ATTACK_TIME)
	{
		isthrow = false;
		action_time = 0;
	}
	else if (isthrow)
	{
		// kết thúc sprite đánh dao mới xuất hiện
		if (animations[SIMON_ANI_ATTACK_RIGHT]->GetCurrentFrame() == 2 || animations[SIMON_ANI_ATTACK_LEFT]->GetCurrentFrame() == 2)
		{

			if (skill->get_isHidden())
			{
				this->skill[0]--;
				skill->nx = this->nx;
				skill->SetPosition(x, y+5);
				skill->startThrow();
			}
		}
	}
	// invisible
	if (isInvisible)
	{
		if (GetTickCount() - invisible_time > SIMON_INVISIBLE_TIME)
		{
			isInvisible = false;
			invisible_time = 0;

			StartUntouchable();
		}
	}

	if (untouchable == 1)
	{
		if (GetTickCount() - untouchable_start > untouchable_time)
		{
			untouchable_start = 0;
			untouchable = 0;
			alpha = 255;
		}
	}

	if (isOnJump && jumpingMove)
	{
		jump_nx ? vx = SIMON_WALKING_SPEED : vx = -SIMON_WALKING_SPEED;
	}

	for (unsigned int i = 0; i < coObjects->size(); i++)
	{

		if (dynamic_cast<CSObject *>(coObjects->at(i)) && coObjects->at(i)->state != SOBJECT_HIDDEN)
		{
			if (isOverlapping(coObjects->at(i)))
			{
				// Lụm roi
				if (coObjects->at(i)->state == CANE_ITEM)
				{
					startPick();
					weapon->IncreaseLevel();
				}

				// Lụm dao
				else if (coObjects->at(i)->state == KNIFE_ITEM)
				{
					skill->SetState(STATE_KNIFE);
					skill->SetNextState(STATE_KNIFE);
					canStop = false;
				}

				// lụm nước thánh
				else if (coObjects->at(i)->state == HOLY_WATER_ITEM)
				{
					skill->SetState(STATE_HOLY_WATER);
					skill->SetNextState(STATE_HOLY_WATER);
					canStop = false;
				}
				// lụm rìu
				else if (coObjects->at(i)->state == AXE_ITEM)
				{
					skill->SetState(STATE_AXE);
					skill->SetNextState(STATE_AXE);
					canStop = false;
				}
				else if (coObjects->at(i)->state == OTHER_STUFF_1)
					isHasOtherStuff = true;
				else if (coObjects->at(i)->state == STOPWATCH_ITEM)
				{
					skill->SetState(STATE_TOPWATCH);
					canStop = true;
				}
				else if (coObjects->at(i)->state == STATE_INVINCIBILITY_POTION)
				{
					startInvisible();
				}
				if (coObjects->at(i)->state == MONEY_ITEM_100)
				{
					CEffect * effect = new CEffect();
					effect->SetPosition(x - 5.0f, y - 10.0f);
					effect->StartShowEffect();
					effect->SetState(STATE_MONEY_100);
					CMap::GetInstance()->PushEffect(effect);
				}
				else if (coObjects->at(i)->state == MONEY_ITEM_400)
				{
					CEffect * effect = new CEffect();
					effect->SetPosition(x - 5.0f, y - 10.0f);
					effect->StartShowEffect();
					effect->SetState(STATE_MONEY_400);
					CMap::GetInstance()->PushEffect(effect);
				}
				else if (coObjects->at(i)->state == MONEY_ITEM_700)
				{
					CEffect * effect = new CEffect();
					effect->SetPosition(x - 5.0f, y - 10.0f);
					effect->StartShowEffect();
					effect->SetState(STATE_MONEY_700);
					CMap::GetInstance()->PushEffect(effect);
				}
				else if (coObjects->at(i)->state == MONEY_ITEM_1k)
				{
					CEffect * effect = new CEffect();
					effect->SetPosition(x - 5.0f, y - 10.0f);
					effect->StartShowEffect();
					effect->SetState(STATE_MONEY_1K);
					CMap::GetInstance()->PushEffect(effect);
				}
				coObjects->at(i)->isHidden = true;
			}
		}

	}
	if (coEvents.size() == 0) //khong co vam cham
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		if (ny < 0)
		{
			if (isJump)
			{
				isJump = false;
				isOnJump = false;
				isSit = true;
			}
		}

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CGround *>(e->obj))
			{
				if (ny < 0)
				{
					if (isJump) isSit = true;
					isOnJump = false;
						basicCollision(min_tx, min_ty, nx, ny);
					//if (isOverlapping(e->obj)) basicCollision(min_tx, min_ty, nx, ny);
				}
				else
				{
					x += dx;
					y += dy;
				}
			}

			if (dynamic_cast<CSObject *>(e->obj) && !e->obj->get_isHidden())
			{

				// Lụm roi
				if (e->obj->state == CANE_ITEM)
				{
					startPick();
					weapon->IncreaseLevel();
				}

				// Lụm dao
				else if (e->obj->state == KNIFE_ITEM)
				{
					skill->SetState(STATE_KNIFE);
					skill->SetNextState(STATE_KNIFE);
					canStop = false;
				}

				// lụm nước thánh
				else if (e->obj->state == HOLY_WATER_ITEM)
				{
					skill->SetState(STATE_HOLY_WATER);
					skill->SetNextState(STATE_HOLY_WATER);
					canStop = false;
				}
				// lụm rìu
				else if (e->obj->state == AXE_ITEM)
				{
					skill->SetState(STATE_AXE);
					skill->SetNextState(STATE_AXE);
					canStop = false;
				}
				else if (e->obj->state == STOPWATCH_ITEM)
				{
					skill->SetState(STATE_TOPWATCH);
					canStop = true;
				}
				else if (e->obj->state == HEART_ITEM)
				{
					this->skill[0] += INCREASE_SKILL_BIG;
				}
				else if (e->obj->state == HEART_SMALL_ITEM)
				{
					this->skill[0] += INCREASE_SKILL_SMALL;
				}
				else if (e->obj->state == STATE_INVINCIBILITY_POTION)
				{
					startInvisible();
				}
			
				e->obj->SetState(SOBJECT_HIDDEN);
				e->obj->isHidden = true;
				
			}
		}

	}


	for (UINT i = 0; i < coEvents.size(); i++)
	{
		delete coEvents[i];
	}
}

void CSimon::Render()
{
	int ani;
	if (isPick)
		{
			nx > 0 ? ani = SIMON_ANI_PICK_RIGHT : ani = SIMON_ANI_PICK_LEFT;
			untouchable = true;
		}
	else
		{
			if (nx > 0)
			{
				if (isJump && !isAttack && !isthrow) ani = SIMON_ANI_SIT_RIGHT;
				else if (isAttack || isthrow) isSit ? ani = SIMON_ANI_SIT_ATTACK_RIGHT : ani = SIMON_ANI_ATTACK_RIGHT;
				else if (state == SIMON_STATE_WALKING_RIGHT && !isJump && !isAttack) ani = SIMON_ANI_WALKING_RIGHT;
				else if (isSit) ani = SIMON_ANI_SIT_RIGHT;
				else ani = SIMON_ANI_IDLE_RIGHT;
			}
			else
			{
				if (isJump && !isAttack && !isthrow) ani = SIMON_ANI_SIT_LEFT;
				else if (isAttack || isthrow) isSit ? ani = SIMON_ANI_SIT_ATTACK_LEFT : ani = SIMON_ANI_ATTACK_LEFT;
				else if (state == SIMON_STATE_WALKING_LEFT && !isJump && !isAttack) ani = SIMON_ANI_WALKING_LEFT;
				else if (isSit) ani = SIMON_ANI_SIT_LEFT;
				else ani = SIMON_ANI_IDLE_LEFT;
			}
		}
	
	

	if (isthrow && canStop) nx > 0 ? ani = SIMON_ANI_IDLE_RIGHT : ani = SIMON_ANI_IDLE_LEFT;

	if (untouchable) alpha == 255 ? alpha = 128 : alpha = 255;
	if (isInvisible) alpha = 0;
	animations[ani]->Render(x, y, alpha);

	if (renderBBox)RenderBoundingBox();

}

void CSimon::SetState(int state)
{

	CGameObject::SetState(state);

	if (isBeMoving)
		return;

	switch (state)
	{
	case SIMON_STATE_WALKING_LEFT:
		 if (!isAttack)
		{
			isSit ? resetSit() : vx = -SIMON_WALKING_SPEED;
		}
		resetSit();
		nx = -1;
		break;
	case SIMON_STATE_WALKING_RIGHT:
		 if (!isAttack)
		{
			isSit ? resetSit() : vx = SIMON_WALKING_SPEED;
		}

		nx = 1;
		break;
	case SIMON_STATE_ATTACK:
		if (isJump && vx != 0)
		{
			isOnJump = true;
			jumpingMove = true;
		}
		startAttack();
		break;
	case SIMON_STATE_THROW:
		startThrow();
		break;
	case SIMON_STATE_PICK:
		startPick();
		break;
	default:
		if (!isJump && !isOnJump) vx = 0;
		if (!isAttack) resetSit();
		break;
	}
}

void CSimon::startAttack()
{
	if (!isPick && !isAttack)
	{
		isAttack = true;
		action_time = GetTickCount();

		CWeapon* weapon = CWeapon::GetInstance();
		nx > 0 ? weapon->SetState(STATE_ATTACK_RIGHT) : weapon->SetState(STATE_ATTACK_LEFT);

		weapon->ResetAttack();
		weapon->SetPosTemp(x, y);
		weapon->set_isHidden(false);

	}
}

void CSimon::startJump()
{
	// Đang lụm, đánh thì không cho nhảy
	if (!isPick && !isAttack && !isJump)
	{

		SetState(SIMON_STATE_JUMP);

		isJump = true;
		vy = -SIMON_JUMP_SPEED_Y;
		jumpingMove = false;
	}
}

void CSimon::startJumpMove(bool nxx)
{
	isJump = true;
	vy = -SIMON_JUMP_SPEED_Y;
	nxx ? vx = SIMON_WALKING_SPEED : vx = -SIMON_WALKING_SPEED;
	jumpingMove = true;
	jump_nx = nxx;
}

void CSimon::startPick()
{
	
		isPick = true;
		isAttack = false;
		isthrow = false;
		action_time = GetTickCount();
		vx = 0;
	
}

void CSimon::startSit(bool sit)
{
	// Đang lụm, đánh, ngồi thì không cho ngồi
	if (!isPick && !isAttack && !isSit)
	{
		isSit = true;
		dx = 0;
		y += SIMON_RESET_BBOX;
	}
}

void CSimon::resetSit()
{
	if (isSit )
	{
		upBBox();
		isSit = false;
	}
}

void CSimon::startThrow()
{
	CSkill* skill = CSkill::GetInstance();
	if (skill->state == STATE_HIDDEN) return;

	if (canStop)
	{
		CMap* map = CMap::GetInstance();
		isthrow = true;
	}
	else
	{
		if (!isPick && !isAttack && !isthrow && skill->get_isHidden())
		{
			if (this->skill[0] > 0)
			{
				isthrow = true;
				action_time = GetTickCount();
				vx = 0;
			}
		}
	}
}

void CSimon::startInvisible()
{
	if (!isInvisible)
	{
		isInvisible = true;

		invisible_time = GetTickCount();
		untouchable_time = SIMON_UNTOUCHABLE_INVISIBLE_TIME;
	}
}

void CSimon::beMoving(int bnx, float bx, int updown)
{
		isBeMoving = true;
		be_nx = bnx;
		be_updown = updown;
}

void CSimon::upBBox()
{
	if ((isSit || isJump))
	{
		y -= SIMON_RESET_BBOX;
	}
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;

	if (isSit)
	{
		right = left + SIMON_SIT_BBOX_WIDTH;
		bottom = top + SIMON_SIT_BBOX_HEIGHT;
	}
	else if (isJump && state)
	{
		right = left + SIMON_SIT_BBOX_WIDTH;
		bottom = top + SIMON_SIT_BBOX_HEIGHT;
	}
	else
	{
		right = left + SIMON_BBOX_WIDTH;
		bottom = top + SIMON_BBOX_HEIGHT;
	}
}

void CSimon::SetIsBlock(bool block)
{
	isBlock = block;
}

CSimon* CSimon::__instance = NULL;
CSimon * CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}

void CSimon::resetDie()
{
	
}