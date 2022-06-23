#pragma once
#include "Player.h"
#include "Door.h"
#include <utility>
#include "Level.h"
#include "BGItems.h"
#include "InvisibleWall.h"
#include "Tapiz.h"
#include "ObjetosInteracbles.h"
#include "LevelState.h"
#include "CamBoundArea.h"
//enemies
#include "Spawner.h"
#include "NPC.h"
#include "Postit.h"
struct LevelLayerInfo {
	std::pair<unsigned char*, PlaceableObject*> level[LEVELSIZEX][LEVELSIZEY];
	std::pair<unsigned char*, PlaceableObject*>* baselayer[LEVELSIZEX];
};

struct LevelInfo {
	LevelLayerInfo levelLayers[nLevelLayers];
	LevelLayerInfo waves[nLevelWaves];
	int* nWaves;
};

struct PlaceableObjectInfo {
	std::string name;  
	PlaceableObject* list;
	PlaceableObjectInfo(std::string name, PlaceableObject* list) : name(name), list(list) {};
};



struct Glosario {
	std::vector<std::vector<int>> dirs;
};

struct ObjectPlacer
{
	std::vector < std::vector<PlaceableObjectInfo>> globalPlaceableObjects;
	std::vector < std::vector<PlaceableObjectInfo>> globalActualPlaceableObjects;
	std::vector < std::vector<int>> usedPlaceableObjects;
	Level* currentLevel;
	int currentBrushNumber;
	int currentWaveNumber;
	LevelInfo levelTemp;;
	std::vector<PlaceableObjectInfo> placeableObjectsLists[nLevelLayers];
	PlaceableObject* Place(int ID, Vector2 pos);
	void FillList();
	void ReplaceAllofAnObject(int ID);
	void EmptyLevel();
	void LoadLevel(Level* l, bool exists);
	void LoadWaveinEditor(Level* l, int nwave);
	Vector2 GetTilePosFromTileCoor(Vector2 p);
	std::vector<PlaceableObject*> GetAllOfAnObject(int n, int l = -1, int w = -1);
	void EraseAllOfAnObject(int ID);
	void PushAllOfAnObject(int ID);
	void EraseFromGlosary(int ID);
	int GetCorrectLayer(int i);
	PlaceableObject* GetCurrentSelectedPO(int ID);
	void AddNewLayer();

	void AddNewBGItem();
};


