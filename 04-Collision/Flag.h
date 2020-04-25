#pragma once
#include "GameObject.h"
#include "LoadResource.h"

#define STATE_DOOR	0

#define ANI_DOOR_CLOSE		0
#define ANI_DOOR_OPENING	1
#define ANI_DOOR_OPEN		2
#define ANI_DOOR_CLOSing	3

class CFlag : public CGameObject
{
	int width;
	int height;

	bool door_opening;
	bool door_opened;
	bool door_close;
public:
	void setSize(int w, int h);
	void setOpening(bool opening) { door_opening = opening; }
	void setOpened(bool opened) { door_opened = opened; }
	void setClose() { door_close = true; door_opened = false; }

	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	CFlag();
};