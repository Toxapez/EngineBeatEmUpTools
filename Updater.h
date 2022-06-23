#pragma once
#include "GameObject.h"
#include "Stat.h"
class Updater : public GameObject
{
	void Update() {
		Stat::UpdateAll();
	}
	static Updater instance;
};

