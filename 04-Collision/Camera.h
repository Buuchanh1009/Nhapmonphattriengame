#pragma once
#include <algorithm>
#include <d3dx9.h>
#include <d3d9.h>

#include "Map.h"
#include "Game.h"
#include "GameObject.h"
#include "Flag.h"
#include "MapManager.h"
#include "Simon.h"

class Camera
{
	static Camera* __instance;

	float cam_x;
	float pos_max;
	bool isFollowSimon;
	bool isAuto;

public:

	void Update(DWORD dt, CGameObject* simon);
	void FollowSimon(CGameObject* simon);
	void StartAuto();
	void SetFollowSimon() { isFollowSimon = true; isAuto = false; }
	void SetAuto() { isAuto = true;}
	bool GetCameraAuto() { return isAuto; }
	bool GetFollowSimon() { return isFollowSimon; }
	float GetCamX() { return cam_x; }


	static Camera* GetInstance();
	Camera() { isFollowSimon = true; }
};