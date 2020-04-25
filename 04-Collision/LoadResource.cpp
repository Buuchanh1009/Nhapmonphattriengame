#include "Textures.h"
#include "Sprites.h"
#include "LoadResource.h"
#include <fstream>
#include <string>

#include "Contands.h"

// convert string to LPCWSTR copy in google
wstring s2ws(string s) {

	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
};

void CLoadResourcesHelper::LoadAllTextures()
{
	CTextures * textures = CTextures::GetInstance();

	ifstream in;
	in.open(TEX_PATH, ios::in);

	if (in.fail())
	{
		OutputDebugString(L"[ERROR] Load texture failed ! \n");
		return;
	}
	while (!in.eof())
	{
		int tex_id, r, g, b;
		string imagePathString;

		in >> tex_id;
		in >> imagePathString;
		in >> r;
		in >> g;
		in >> b;

		wstring tempPath = s2ws(imagePathString);
		LPCWSTR imagePath = tempPath.c_str();


		textures->Add(tex_id, imagePath, D3DCOLOR_XRGB(r, g, b));
	}

	in.close();
}

void CLoadResourcesHelper::LoadSprites(string filePath)
{
	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	LPDIRECT3DTEXTURE9 tex;
	ifstream in;
	in.open(filePath, ios::in);

	if (in.fail())
	{
		OutputDebugString(L"[ERROR] Load sprites failed ! \n");
		return;
	}
	while (!in.eof())
	{
		int id_tex;
		int id, l, t, r, b;

		in >> id_tex;
		tex = textures->Get(id_tex);

		in >> id;
		in >> l;
		in >> t;
		in >> r;
		in >> b;
		sprites->Add(id, l, t, r, b, tex);
	}

	in.close();
}

void CLoadResourcesHelper::LoadAnimations(string filePath, CGameObject* object)
{
	LPANIMATION ani;
	CAnimations *animations = CAnimations::GetInstance();

	ifstream in;
	in.open(filePath, ios::in);

	if (in.fail())
	{
		OutputDebugString(L"[ERROR] Load animations failed ! \n");
		return;
	}

	while (!in.eof())
	{
		int time, n, ani_id;
		in >> time;
		in >> n;

		ani = new CAnimation(time);
		for (int i = 0; i < n; i++)
		{
			int id;
			in >> id;
			ani->Add(id);
		}

		in >> ani_id;

		animations->Add(ani_id, ani);
		object->AddAnimation(ani_id);
	}

	in.close();
}