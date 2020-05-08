#include "TileMat.h"



void CTileMat::Render()
{
	CSprites *sprites = CSprites::GetInstance();

	sprites->Get(id)->Draw(index_y*tile_size_x -1, index_x * tile_size_y + 20 + BOARDGAME_HEIGHT);
}

void CTileMat::SetTileSize(int size_x, int size_y)
{
	this->tile_size_x = size_x;
	this->tile_size_y = size_y;
}


CTileMat::CTileMat(int id, int x, int y)
{
	this->id = id;
	this->index_x = x;
	this->index_y = y;
}