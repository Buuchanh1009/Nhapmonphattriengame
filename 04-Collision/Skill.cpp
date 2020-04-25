#include "Skill.h"
#include "SObject.h"
#include "Simon.h"
#include "Effect.h"
#include "Ground.h"

CSkill::CSkill()
{
	CLoadResourcesHelper::LoadSprites("data\\skills\\skill_sprites.txt");
	CLoadResourcesHelper::LoadAnimations("data\\skills\\skill_anis.txt", this);
	state = STATE_HIDDEN;
	nextState = STATE_HIDDEN;
}

void CSkill::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (state != STATE_KNIFE && state != STATE_ACE )
		vy += SKILL_SPEED_1 * dt;
	else if (state == STATE_ACE)
		vy += SKILL_SPEED_AXE_Y * dt;
	else vy = 0;
		
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();



	if (state != STATE_KNIFE && state != STATE_ACE)
	{
		CalcPotentialCollisions(coObjects, coEvents);
	}

	if (GetTickCount() - timethrow_start > timeshow)
	{

		set_isHidden(true);
		timethrow_start = 0;
		isFailing = false;
	}
	else
	{
		updateThrow();
	}

	if (coEvents.size() == 0 )
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

		}

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		delete coEvents[i];
	}
}

void CSkill::Render()
{
	int ani;


	if (state == STATE_KNIFE)
	{
		nx < 0 ? ani = ANI_THROW_KNIFE_LEFT : ani = ANI_THROW_KNIFE_RIGHT;
	}
	else if (state == STATE_ACE)
	{
		nx < 0 ? ani = ANI_ACE_LEFT : ani = ANI_ACE_RIGHT;
	}

	if (!isHidden && state != STATE_TOPWATCH && state != STATE_HIDDEN)
	{
		animations[ani]->Render(x, y);
		if (renderBBox)RenderBoundingBox();
	}
}

void CSkill::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;

	if (state == STATE_KNIFE)
	{
		right = x + KNIFE_WIDTH;
		bottom = y + KNIFE_HEIGHT;
	}
	else if (state == STATE_ACE)
	{
		right = x + ACE_WIDTH;
		bottom = y + ACE_HEIGHT;
	}
}

void CSkill::startThrow()
{
	if (isHidden)
	{
		isHidden = false;

		timethrow_start = GetTickCount();

		SetState(nextState);
	}
}

void CSkill::updateThrow()
{
	if (state == STATE_KNIFE && !isHidden)
	{
		nx > 0 ? dx = 3 : dx = -3;
	}
	else if (state == STATE_ACE)
	{
		nx > 0 ? vx = SKILL_SPEED_AXE_X : vx = -SKILL_SPEED_AXE_X;
	}
}

void CSkill::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	
	case STATE_ACE:
		timeshow = TIME_THROW;
		vy = -SKILL_SPEED_AXE;
		break;
	default:
		timeshow = TIME_THROW;
		break;
	}
}

CSkill* CSkill::__instance = NULL;
CSkill * CSkill::GetInstance()
{
	if (__instance == NULL) __instance = new CSkill();
	return __instance;
}