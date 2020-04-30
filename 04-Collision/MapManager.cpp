#include <fstream>
#include <string>

#include "MapManager.h"
///#include "Simon.h"

CMapManager::CMapManager()
{
	map = CMap::GetInstance();
}

void CMapManager::LoadMapResources()
{
	ifstream in;
	in.open("data\\background\\map_manager.txt", ios::in);

	if (in.fail())
	{
		OutputDebugString(L"[ERROR] Load map manager failed ! \n");
		return;
	}
	while (!in.eof())
	{
		int stage;
		string filePath;

		in >> stage >> filePath;

		if (stage == this->map_stage)
		{
			map->LoadContent(filePath);
			break;
		}
	}
	in.close();
}

void CMapManager::DrawMap()
{
	map->DrawMap();
}

void CMapManager::ChangeMap(int map)
{
	map_stage = map;
	LoadMapResources();
	/*CSimon::GetInstance()->resumeTime();*/
}

void CMapManager::LoadRoundGame(int round)
{
	map_stage = round;
	LoadMapResources();
	DrawMap();
}

CMapManager* CMapManager::__instance = NULL;
CMapManager * CMapManager::GetInstance()
{
	if (__instance == NULL) __instance = new CMapManager();
	return __instance;
}