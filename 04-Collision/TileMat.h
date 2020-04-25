#pragma once

#include "GameObject.h"
#include "Contands.h"

class CTileMat
{
	int id;

	int index_x;
	int index_y;

	int tile_size_x;
	int tile_size_y;

public:
	
	void Render();
	int GetId() { return id; }
	void SetTileSize(int size_x, int size_y);

	CTileMat() { ; }
	CTileMat(int id, int x, int y);
	~CTileMat() { ; }
};