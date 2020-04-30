#pragma once
#include "GameObject.h"

class CGround : public CGameObject
{
	int width;
	int height;

public:
	void setSize(int w, int h);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};