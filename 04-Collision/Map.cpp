#include "Map.h"
#include <fstream>
#include "Game.h"
#include "Simon.h"
#include "Ground.h"
#include "Weapon.h"
#include "Skill.h"

CGround* ground;
CSObject* sobject;


//void CMap::push(int value)
//{
//	gridObject.push_back(value);
//}
//vector<vector<int>>CMap::Get_Arr()
//{
//	vector<int>temp;
//	gridObject.push_back(temp);
//	return gridObject;
//}


void CMap::LoadMapSprites()
{
	CLoadResourcesHelper::LoadSprites("data\\background\\background_sprites.txt");
	
}

void CMap::LoadContent(string filePath)
{
	ResetListObjects();

	ifstream in;
	in.open(filePath, ios::in);

	if (in.fail())
	{
		OutputDebugString(L"[ERROR] Load map content failed ! \n");
		return;
	}

	CTileMat* tile;
	mapObjects.clear();
	gridObject.clear();
	/*mapObjectId = 2;*/

	while (!in.eof())
	{

		// background
		in >> this->max_x >> this->max_y >> this->tile_size_x >> this->tile_size_y >> this->pos_max >> this->pos_door;
		for (int i = 0; i < max_y; i++)
		{
			for (int j = 0; j < max_x; j++)
			{
				int id;
				in >> id;

				tile = new CTileMat(id, i, j);
				tile->SetTileSize(tile_size_x, tile_size_y);
				tiles.push_back(tile);
			}
		}

		CSimon* simon = CSimon::GetInstance();

		while (!in.eof())
		{
			mapObjectId++;

			int id_object;
			in >> id_object;

			if (id_object == 0) 
			{
				int size_x, size_y, x, y;
				in >> size_x >> size_y >> x >> y;
				y += BOARDGAME_HEIGHT;

				ground = new CGround();
				ground->setSize(size_x, size_y);
				ground->SetPosition(float(x), float(y));

				mapObjects[mapObjectId] = ground;
				vector<int> goundGrid = GetGridNumber(float(x), size_x);
				for (int i = 0; i < goundGrid.size(); i++)
				{
					AddGridObject(goundGrid[i], mapObjectId);
				}
			}
			else if (id_object == 1)
			{
				int x, y;
				in >> x >> y;
				y += BOARDGAME_HEIGHT;

				simon = CSimon::GetInstance();
				simon->SetPosition(float(x), float(y));
			}
			else if (id_object == 2)
			{
				int x, y, state, nextState;
				in >> x >> y >> state >> nextState;
				y += BOARDGAME_HEIGHT;

				sobject = new CSObject();
				sobject->SetPosition(float(x), float(y));
				sobject->SetState(state);
				sobject->SetNextState(nextState);
				mapObjects[mapObjectId] = sobject;
				AddGridObject(GetGridNumber(x), mapObjectId);
			}
		}
	}
	in.close();
}

void CMap::DrawMap()
{
	int tile_x_begin = CGame::GetInstance()->getCamPos_x() / tile_size_x;

	int tile_x_end = tile_x_begin + SCREEN_WIDTH / tile_size_x + 1;

	//int ncount = 0;

	for (unsigned int i = tile_x_begin; i < tiles.size(); i++)
	{
		tiles[i]->Render();
	}

	//OutputDebugString(L"a");
}

//vector<LPGAMEOBJECT> CMap::Get_coObjectFlag()
//{
//	vector<LPGAMEOBJECT> coObjectFlag;
//	return coObjectFlag;
//}

vector<LPGAMEOBJECT> CMap::Get_listEffect()
{
	vector<LPGAMEOBJECT> effects;

	for (unsigned int i = 0; i < listEffect.size(); i++)
	{
		if (!listEffect[i]->isHidden)
		{
			effects.push_back(listEffect[i]);
		}
	}

	if (effects.size() == 0) listEffect.clear();

	return effects;
}

vector<LPGAMEOBJECT> CMap::Get_listItem()
{
	vector<LPGAMEOBJECT> items;

	for (unsigned int i = 0; i < listItem.size(); i++)
	{
		if (!listItem[i]->get_isHidden())
		{
			items.push_back(listItem[i]);
		}
	}

	if (items.size() == 0) listItem.clear();

	return items;
}

void CMap::PushEffect(LPGAMEOBJECT effect)
{
	listEffect.push_back(effect);
}

void CMap::PushEffect(float xx, float xy)
{
	CEffect * effect = new CEffect();
	effect->SetPosition(xx,xy);
	effect->StartShowEffect();
	listEffect.push_back(effect);
}

void CMap::PushItem(CSObject* item)
{
	listItem.push_back(item);
}

void CMap::PushObject(LPGAMEOBJECT object)
{
	int numGrid = GetGridNumber(CSimon::GetInstance()->x);
	mapObjectId++;
	mapObjects[mapObjectId] = object;
	gridObject.at(numGrid).push(mapObjectId);
}


void CMap::ActiveMoney1K()
{
	if (money1k != NULL)
	{
		money1k->SetState(money1k->nextState);
		money1k->isHidden = false;
	}
}

CMap::CMap()
{
	LoadMapSprites();
}

CMap* CMap::__instance = NULL;
CMap * CMap::GetInstance()
{
	if (__instance == NULL) __instance = new CMap();
	return __instance;
}

LPGAMEOBJECT CMap::Get_mapObject(unsigned int id)
{
	return mapObjects[id];
}

void CMap::AddMapObject(int id, LPGAMEOBJECT obj)
{
	mapObjects[id] = obj;
}

void CMap::AddGridObject(int numGrid, int id)
{
	while (gridObject.size() <= numGrid)
	{
		intg temp;
		gridObject.push_back(temp);
	}

	gridObject.at(numGrid).push(id);
}

int CMap::GetGridNumber(int pos_x)
{
	return pos_x / SCREEN_WIDTH;
}

vector<int> CMap::GetGridNumber(float pos_x, int size_x)
{
	int left = pos_x / SCREEN_WIDTH; 
	int right = (pos_x + size_x) / SCREEN_WIDTH; 
	vector<int> result;

	if (left < right) // nam o nhieu grid
	{
		for (int i = left; i <= right; i++)
		{
			result.push_back(i);
		}
	}
	else // (left = right) nam trong 1 grid
		result.push_back(left);

	return result;
}

void CMap::Get_gridObjects( vector<LPGAMEOBJECT> &coObjectsFull,vector<LPGAMEOBJECT> &coObjectGround,vector<LPGAMEOBJECT> &coObjectsWithSimon,vector<LPGAMEOBJECT> &coObjectsWithSkill
)
{
	coObjectsFull.clear();
	coObjectGround.clear();
	coObjectsWithSimon.clear();
	coObjectsWithSkill.clear();

	vector<int> currentGrid = GetGridNumber(CGame::GetInstance()->getCamPos_x(), SCREEN_WIDTH );
	unordered_map<int, int> checkUnique; 
	vector<int> idObjects;

	for (int i = 0; i < currentGrid.size(); i++)
	{
		idObjects = gridObject[currentGrid[i]].Get_Arr();

		for (int j = 0; j < idObjects.size(); j++)
		{
			if (checkUnique[idObjects[j]] == NULL && !mapObjects[idObjects[j]]->get_isHidden())//kt xem doi tuong da ton tai hay chua
			{
				coObjectsFull.push_back(mapObjects[idObjects[j]]);
				checkUnique[idObjects[j]] = idObjects[j];

				if (dynamic_cast<CSObject *>(mapObjects[idObjects[j]])) //&& !mapObjects[idObjects[j]]->get_isHidden()
				{
					if (mapObjects[idObjects[j]]->GetState() == SMALL_CANDLE || mapObjects[idObjects[j]]->GetState() == BIG_CANDLE) //vk va cham voi do vat
					{
						coObjectsWithSkill.push_back(mapObjects[idObjects[j]]);
					}
					else if (mapObjects[idObjects[j]]->GetState() != STATE_HIDDEN) // simon va cham voi do vat
					{
						coObjectsWithSimon.push_back(mapObjects[idObjects[j]]);
					}
					if (mapObjects[idObjects[j]]->GetNextState() == MONEY_ITEM_1k)
						money1k = mapObjects[idObjects[j]];
				}
				else if (dynamic_cast<CGround *>(mapObjects[idObjects[j]])) //gach
				{
					coObjectGround.push_back(mapObjects[idObjects[j]]);
					coObjectsWithSkill.push_back(mapObjects[idObjects[j]]);
					coObjectsWithSimon.push_back(mapObjects[idObjects[j]]);
				}
			}
		}
	}

	CWeapon* weapon = CWeapon::GetInstance();
	CSimon* simon = CSimon::GetInstance();

	CSkill* skill = CSkill::GetInstance();
	coObjectsFull.push_back(weapon);
	coObjectsFull.push_back(simon);
	coObjectsFull.push_back(skill);
}

void CMap::ResetListObjects()
{
	tiles.clear();
	listEffect.clear();
	gridObject.clear();
	mapObjects.clear();
	listItem.clear();
}