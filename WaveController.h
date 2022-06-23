#pragma once
#include "LevelEditor.h"
#include "GameObject.h"
class WaveController : public GameObject
{
	static WaveController instance;
	void Update();
	void Draw();
};

