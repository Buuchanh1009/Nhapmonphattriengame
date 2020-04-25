#include "Flag.h"
#include "Simon.h"
#include "Camera.h"

CFlag::CFlag()
{
	CLoadResourcesHelper::LoadSprites("data\\flags\\flag_sprites.txt");
	CLoadResourcesHelper::LoadAnimations("data\\flags\\flag_anis.txt", this);
}

void CFlag::setSize(int w, int h)
{
	this->width = w;
	this->height = h;
}

void CFlag::Render()
{
	/*if (state == STATE_DOOR)
	{
		int ani;				

		if (door_opening) ani = 1;
		else if (door_opened) ani = 2;
		else if (door_close) ani = 3;
		else ani = 0;

		if (animations[ANI_DOOR_OPENING]->get_countAni() >= 1 && door_opening)
		{
			door_opening = false;
			door_opened = true;
			animations[ANI_DOOR_OPENING]->set_countAni(0);

			CSimon::GetInstance()->SetBeMoving(true);
		}
		if (animations[ANI_DOOR_CLOSing]->get_countAni() >= 1 && door_close)
		{
			door_opening = false;
			door_opened = false;
			door_close = false;
			animations[ANI_DOOR_CLOSing]->set_countAni(0);

			Camera::GetInstance()->SetNextMap();
			Camera::GetInstance()->StartAuto();
		}

		animations[ani]->Render(x, y, 255);
	}*/

	if (renderBBox)RenderBoundingBox();
}

void CFlag::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + this->width;
	bottom = top + this->height;
}