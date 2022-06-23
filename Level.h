#pragma once
#include "Vector2.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>

const unsigned char EMPTYTILEVALUE = 255;
const int LEVELTILESIZE = 100;
const int LEVELSIZEX = 200;
const int LEVELSIZEY = 200;
const int nLevelLayers = 6;
const int nLevelWaves = 32;

struct LevelLayer {
	unsigned char content[LEVELSIZEX][LEVELSIZEY];
};

struct Level
{
	Level();
	char name[30];
	int nWaves;
	LevelLayer waves[nLevelWaves];
	LevelLayer levelLayers[nLevelLayers];
	void SetName(const char* tName);
	void Save(std::vector<std::string>* config, std::vector<std::string>* waveconfig, std::vector < std::vector<int>> glosario);
	void Load(std::string n, std::vector<std::string>* config, std::vector<std::string>* waveconfig, std::vector < std::vector<int>>* glosario);
	void Delete();
};

