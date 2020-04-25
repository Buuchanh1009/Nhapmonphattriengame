#include <windows.h>
#include<fstream>

#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Map.h"
#include "MapManager.h"
#include "Camera.h"
#include "LoadResource.h"
#include "Contands.h"
#include "Ground.h"
#include "Simon.h"
#include "SObject.h"
#include "Weapon.h"
#include "Skill.h"


using namespace std;

CGame *game;
CMapManager* map_manager;
Camera* camera;
CMap* map;
CSimon *simon;

vector<LPGAMEOBJECT> coObjectsFull;
vector<LPGAMEOBJECT> coObjectGround;
vector<LPGAMEOBJECT> coObjectFlag;
vector<LPGAMEOBJECT> coObjectsWithSimon;
vector<LPGAMEOBJECT> coObjectsWithSkill;
vector<LPGAMEOBJECT> listEffect;
vector<LPGAMEOBJECT> listItem;

class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void LoadRoundGame(int round)
{
	map_manager = CMapManager::GetInstance();
	map_manager->ChangeMap(round);

	Camera::GetInstance()->SetFollowSimon();
}

void toggleRenderBBox()
{
	for (unsigned int i = 0; i < coObjectsFull.size(); i++)
	{
		coObjectsFull[i]->toggleRenderBBox();
	}
}

void onFlag(int st)
{
	for (unsigned int i = 0; i < coObjectFlag.size(); i++)
	{
		if (simon->isOverlapping(coObjectFlag[i]) && !simon->get_isBeMoving())
		{
			if (coObjectFlag[i]->nextState == st)
			{
				simon->beMoving(coObjectFlag[i]->state, coObjectFlag[i]->x, coObjectFlag[i]->nextState);
			}
		}
	}
}

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	if (simon->get_isBlock()) return;
	if (simon->get_isPick()) return;
	if (simon->get_isInjure()) return;
	if (simon->get_isBeMoving()) return;

	switch (KeyCode)
	{
	case DIK_X:
		if (!simon->get_isOnJump())
		{
			if (simon->state == SIMON_STATE_WALKING_RIGHT)simon->startJumpMove(true);
			else if (simon->state == SIMON_STATE_WALKING_LEFT) simon->startJumpMove(false);
			else simon->startJump();	
		}
		break;
	case DIK_Z:
		if (!simon->get_isAttack() && !simon->get_isPick() && !simon->get_isThrow())
		{
			simon->SetState(SIMON_STATE_ATTACK);
		}
		break;
	case DIK_UP:
		if (!simon->get_isJump())
			onFlag(SIMON_UPSTAIR);
		break;
	case DIK_DOWN:
		 if (!simon->get_isAttack() && !simon->get_isPick() && !simon->get_canSit() )
		{
			simon->SetState(SIMON_STATE_SIT);

		}
	
		break;
	
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	if (simon->GetState() == SIMON_STATE_DIE) return;
	if (simon->get_isBlock()) return;
	if (simon->get_isPick()) return;
	if (simon->get_isInjure()) return;
	if (simon->get_isBeMoving()) return;

	if (game->IsKeyDown(DIK_DOWN))
	{
			simon->startSit(true);
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		if (game->IsKeyDown(DIK_Z))
		{
			if (!simon->get_isAttack() && !simon->get_isPick() && !simon->get_isThrow() && !simon->get_isSit())
			{
				simon->SetState(SIMON_STATE_THROW);
			}
		}
		else if (!simon->get_isJump())
		{
			if (simon->get_be_nx() == -1 && simon->get_be_updown() == SIMON_UPSTAIR)  simon->SetState(SIMON_STATE_WALKING_LEFT);
			else if (simon->get_be_nx() == 1 ) simon->SetState(SIMON_STATE_WALKING_LEFT);
			else simon->SetState(SIMON_STATE_WALKING_RIGHT);
		}
	}
	else if (game->IsKeyDown(DIK_RIGHT) && !simon->get_isAttack() && !simon->get_isJump() && !simon->get_isOnJump())
	{
		if (simon->get_isJump())
		{
			if (simon->nx > 0) simon->SetState(SIMON_STATE_WALKING_RIGHT);
		}
		else
		{
			simon->SetState(SIMON_STATE_WALKING_RIGHT);
		}
	}
	else if (game->IsKeyDown(DIK_LEFT) && !simon->get_isAttack() && !simon->get_isJump() && !simon->get_isOnJump())
	{
		if (simon->get_isJump())
		{
			if (simon->nx < 0) simon->SetState(SIMON_STATE_WALKING_LEFT);
		}
		else
		{
			simon->SetState(SIMON_STATE_WALKING_LEFT);
		}
	}
	else
		simon->SetState(SIMON_STATE_IDLE);

}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();
	textures->LoadAllTextures();

	simon = CSimon::GetInstance();
	LoadRoundGame(1);
}


void Update(DWORD dt)
{
	map = CMap::GetInstance();
	map->Get_gridObjects(coObjectsFull, coObjectGround, coObjectFlag, coObjectsWithSimon, coObjectsWithSkill);
	listEffect = map->Get_listEffect();
	listItem = map->Get_listItem();

	vector<LPGAMEOBJECT>  coSimon(coObjectsWithSimon);
	copy(listItem.begin(), listItem.end(), back_inserter(coSimon));

	vector<LPGAMEOBJECT>  coSkill(coObjectsWithSkill);

	for (unsigned int i = 0; i < coObjectsFull.size(); i++)
	{
		if (dynamic_cast<CGround *>(coObjectsFull[i]))
			coObjectsFull[i]->Update(dt, &coObjectsFull);

		else if (dynamic_cast<CSimon *>(coObjectsFull[i]))
			coObjectsFull[i]->Update(dt, &coSimon);

		else if (dynamic_cast<CWeapon *>(coObjectsFull[i]))
		{
			coObjectsFull[i]->Update(dt, &coSkill);
		}

		else if (dynamic_cast<CSObject *>(coObjectsFull[i]))
		{
			coObjectsFull[i]->Update(dt, &coObjectGround);
		}

		else if (dynamic_cast<CSkill *>(coObjectsFull[i]))
		{
			coObjectsFull[i]->Update(dt, &coSkill);
		}

		else
		{
			coObjectsFull[i]->Update(dt, &coObjectsFull);
		}
	}

	if (listEffect.size() > 0)
		for (unsigned int i = 0; i < listEffect.size(); i++)
		{
			listEffect[i]->Update(dt);
		}

	if (listItem.size() > 0)
		for (unsigned int i = 0; i < listItem.size(); i++)
		{
			listItem[i]->Update(dt, &coObjectGround);
		}

	// Update camera to follow simon
	camera = Camera::GetInstance();
	camera->Update(dt, simon);
}

void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		
		map->DrawMap();

		for (unsigned int i = 0; i < coObjectsFull.size(); i++)
		{
			coObjectsFull[i]->Render();
		}

		for (unsigned int i = 0; i < listEffect.size(); i++)
		{
			listEffect[i]->Render();
		}

		for (unsigned int i = 0; i < listItem.size(); i++)
		{
			listItem[i]->Render();
		}
		
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //WHITE_BRUSH
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}