#include "Camera.h"



void Camera::Update(DWORD dt, CGameObject* simon)
{

	if (isFollowSimon && !isAuto)
	{
		FollowSimon(simon);
	}
}

void Camera::FollowSimon(CGameObject* simon)
{
	// Update camera to follow simon
	float cx, cy;
	simon->GetPosition(cx, cy);

	cam_x = CGame::GetInstance()->getCamPos_x();
	pos_max = CMap::GetInstance()->GetPos_max();

	if (cx - SCREEN_WIDTH / 3 < 0)
	{
		cx = 0;
	}
	else if (cx + SCREEN_WIDTH / 3 > pos_max)
	{
		cx = pos_max - SCREEN_WIDTH;
	}
	else
	{
		cx -= SCREEN_WIDTH / 3;
	}


	CGame::GetInstance()->SetCamPos(cx, 0);
	
}

Camera* Camera::__instance = NULL;
Camera * Camera::GetInstance()
{
	if (__instance == NULL) __instance = new Camera();
	return __instance;
}