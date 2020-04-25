#include "Ground.h"

void CGround::setSize(int w, int h)
{
	this->width = w;
	this->height = h;
}

void CGround::Render()
{
	if (renderBBox)RenderBoundingBox();
}

void CGround::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + this->width;
	bottom = top + this->height;
}