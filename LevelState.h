#pragma once
struct LevelState
{
	int currentWave;
	int nEnemies;
	int maxEnemies;
	bool wavesActive = false;
	static LevelState instance;
};

