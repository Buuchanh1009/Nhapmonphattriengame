#pragma once
#include <Windows.h>
#include "math.h"
#include "LoadResource.h"
#include "TileMat.h"
#include "Effect.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "SObject.h"

using namespace std;

class CMap
{
	static CMap* __instance;

	int max_x;
	int max_y;
	int tile_size_x;
	int tile_size_y;
	
	float pos_max;
	int pos_door;
	//vector<int>arr;
	vector<CTileMat*> tiles;
	vector<LPGAMEOBJECT> listEffect;
	vector<LPGAMEOBJECT> listItem;
	
	LPGAMEOBJECT money1k;

	unordered_map<int, LPGAMEOBJECT> mapObjects;
	//vector<vector<int>> gridObject;
	vector<intg> gridObject;
	int mapObjectId;
public :

	CMap();
	/*void push(int value);
	vector<vector<int>> Get_Arr();*/
	void LoadContent(string filePath);
	void LoadMapSprites();
	void DrawMap();
	void ResetListObjects();
	void PushEffect(LPGAMEOBJECT effect);
	void PushEffect(float xx, float xy);
	void PushItem(CSObject* item);
	void PushObject(LPGAMEOBJECT shoot);
	void ActiveMoney1K();

	int GetMaxX() { return this->max_x; }
	int GetMaxY() { return this->max_y; }
	int GetTileSizeX() { return tile_size_x; }
	
	float GetPos_max() { return pos_max; }
	//int GetPos_door() { return pos_door; }

	vector<LPGAMEOBJECT> Get_coObjectFlag();
	vector<LPGAMEOBJECT> Get_listEffect();
	vector<LPGAMEOBJECT> Get_listItem();
	static CMap * GetInstance();

	LPGAMEOBJECT Get_mapObject(unsigned int id);
	void AddMapObject(int id, LPGAMEOBJECT obj);
	void AddGridObject(int numGrid, int id);
	int GetGridNumber(int pos_x);
	vector<int> GetGridNumber(float pos_x, int size_x);
	int Get_mapObjectId() { return mapObjectId; }
	void Get_gridObjects(
		vector<LPGAMEOBJECT> &coObjectsFull,
		vector<LPGAMEOBJECT> &coObjectGround,
		vector<LPGAMEOBJECT> &coObjectFlag,
		vector<LPGAMEOBJECT> &coObjectsWithSimon,
		vector<LPGAMEOBJECT> &coObjectsWithSkill
	);

	~CMap() { ; }
};