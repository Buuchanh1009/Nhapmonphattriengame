#pragma once
#include "GameObject.h"

class CLoadResourcesHelper
{
public:

	void static LoadAllTextures();
	void static LoadSprites(string filePath);
	void static LoadAnimations(string filePath, CGameObject * object);

	CLoadResourcesHelper() { ; }
	~CLoadResourcesHelper() { ; }
};