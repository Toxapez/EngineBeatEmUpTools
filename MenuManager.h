#pragma once
#include "PauseMenu.h"
#include "SetttingsMenu.h"
class MenuManager : public GameObject
{
	static MenuManager instance;
	void AfterStaticStart();
	void Update();
};
