#pragma once
#include "Menu.h"


struct PauseMenu : public Menu
{
	static PauseMenu instance;
	int optionSelected;
	int nOptions;
	void Update();
	void Draw();
	void Open();
	void Close();
	PauseMenu();
	SpriteStatic* windowSpr,*titleSpr, *icon1, *icon2, *icon3, *selectorSpr;
};

