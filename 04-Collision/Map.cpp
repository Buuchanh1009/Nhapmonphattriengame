#include "Map.h"
#include <fstream>
#include "Game.h"
#include "Simon.h"
#include "Ground.h"
#include "Flag.h"
#include "Weapon.h"
#include "Skill.h"

CGround* ground;
CSObject* sobject;


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
	mapObjectId = 2;

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
			else if (id_object == 3)
			{
				int size_x, size_y, x, y, state, nextState;
				in >> size_x >> size_y >> x >> y >> state >> nextState;
				y += BOARDGAME_HEIGHT;

				CFlag* flag = new CFlag();
				flag->setSize(size_x, size_y);
				flag->SetPosition(float(x), float(y));
				flag->SetState(state);
				flag->SetNextState(nextState);

				mapObjects[mapObjectId] = flag;
				vector<int> goundGrid = GetGridNumber(float(x), size_x);
				for (int i = 0; i < goundGrid.size(); i++)
				{
					AddGridObject(goundGrid[i], mapObjectId);
				}
			}
			else if (id_object == 4)
			{
				int x, y, state, nextState, nxx;

				in >> x >> y >> state >> nextState >> nxx;
				y += BOARDGAME_HEIGHT;

				if (state == 3)
				{
					float x_min, x_max;
					in >> x_min >> x_max;
					
				}

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
		//ncount++;

		if (i >= tile_x_end)
		{
			i += max_x - SCREEN_WIDTH / tile_size_x - 2;
			tile_x_end += max_x;
		}
	}

	//OutputDebugString(L"a");
}

void CMap::ResetListObjects()
{
	tiles.clear();
	listEffect.clear();
	gridObject.clear();
	mapObjects.clear();
	listItem.clear();
}

vector<LPGAMEOBJECT> CMap::Get_coObjectFlag()
{
	vector<LPGAMEOBJECT> coObjectFlag;
	vector<int> currentGrid = GetGridNumber(CGame::GetInstance()->getCamPos_x(), SCREEN_WIDTH - 1);
	for (unsigned int i = 0; i < currentGrid.size(); i++)
	{
		vector<int> idObjects = gridObject[currentGrid[i]].Get_Arr();

		for (unsigned int j = 0; j < idObjects.size(); j++)
		{
			if (dynamic_cast<CFlag *>(mapObjects[idObjects[j]]) && !mapObjects[idObjects[j]]->get_isHidden())
			{
				coObjectFlag.push_back(mapObjects[idObjects[j]]);
			}
		}
	}
	return coObjectFlag;
}

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
		int_c temp;
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
	int min = pos_x / SCREEN_WIDTH;
	int max = (pos_x + size_x) / SCREEN_WIDTH;
	vector<int> result;

	if (min < max)
	{
		for (int i = min; i <= max; i++)
		{
			result.push_back(i);
		}
	}
	else
		result.push_back(min);

	return result;
}

void CMap::Get_gridObjects(
	vector<LPGAMEOBJECT> &coObjectsFull,
	vector<LPGAMEOBJECT> &coObjectGround,
	vector<LPGAMEOBJECT> &coObjectFlag,
	vector<LPGAMEOBJECT> &coObjectsWithSimon,
	vector<LPGAMEOBJECT> &coObjectsWithSkill
)
{
	coObjectsFull.clear();
	coObjectGround.clear();
	coObjectFlag.clear();
	coObjectsWithSimon.clear();
	coObjectsWithSkill.clear();


	vector<int> currentGrid = GetGridNumber(CGame::GetInstance()->getCamPos_x(), SCREEN_WIDTH - 1);
	unordered_map<int, int> checkUnique;
	vector<int> idObjects;

	for (int i = 0; i < currentGrid.size(); i++)
	{
		while (gridObject.size() - 1 < currentGrid[currentGrid.size() - 1])
		{
			int_c temp;
			gridObject.push_back(temp);
		}
		idObjects = gridObject[currentGrid[i]].Get_Arr();

		for (int j = 0; j < idObjects.size(); j++)
		{
			if (checkUnique[idObjects[j]] == NULL && !mapObjects[idObjects[j]]->get_isHidden())
			{
				coObjectsFull.push_back(mapObjects[idObjects[j]]);
				checkUnique[idObjects[j]] = idObjects[j];

				if (dynamic_cast<CSObject *>(mapObjects[idObjects[j]])) //&& !mapObjects[idObjects[j]]->get_isHidden()
				{
					if (mapObjects[idObjects[j]]->GetState() == SMALL_CANDLE || mapObjects[idObjects[j]]->GetState() == BIG_CANDLE)
					{
						coObjectsWithSkill.push_back(mapObjects[idObjects[j]]);
					}
					else if (mapObjects[idObjects[j]]->GetState() != STATE_HIDDEN)
					{
						coObjectsWithSimon.push_back(mapObjects[idObjects[j]]);
					}

					if (mapObjects[idObjects[j]]->GetState() == STATE_WALL_1 || mapObjects[idObjects[j]]->GetState() == STATE_WALL_2 || mapObjects[idObjects[j]]->GetState() == STATE_WALL_3) coObjectsWithSkill.push_back(mapObjects[idObjects[j]]);
					if (mapObjects[idObjects[j]]->GetNextState() == MONEY_ITEM_1k)
						money1k = mapObjects[idObjects[j]];
				}
				else if (dynamic_cast<CGround *>(mapObjects[idObjects[j]]))
				{
					coObjectGround.push_back(mapObjects[idObjects[j]]);
					coObjectsWithSkill.push_back(mapObjects[idObjects[j]]);
					coObjectsWithSimon.push_back(mapObjects[idObjects[j]]);
				}
				else if (dynamic_cast<CFlag *>(mapObjects[idObjects[j]]))
				{
					coObjectFlag.push_back(mapObjects[idObjects[j]]);
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