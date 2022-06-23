#pragma once
#include "GameObject.h"
#include "InputManager.h"
#include "SpriteStatic.h"
#include "TextDrawer.h"
#include "FigureDrawer.h"
struct Menu : public GameObject
{
	static std::map<std::string, SpriteStatic> sprites;
	static bool menuManagerIsActive ;
	static std::vector<Menu*> menus;
	bool isOpen;
	Menu();
	virtual void Open();
	virtual void Close();
};

