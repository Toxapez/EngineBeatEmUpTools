#pragma once
#include "Cam.h"
#include "FigureDrawer.h"
#include "Mouse.h"
#include "ObjectPlacer.h"
#include "TextDrawer.h"
#include "GameState.h"
#include "BooleanQuestion.h"
#include "EmergentMessage.h"
#include "Console.h"
#include "OptionsBox.h"
#include "OpenGLClass.h"
class LevelEditor : public GameState
{
	void NewLevel();
	Cam cam;
	void ClearLevelTemp();
	int puttingObjectSelection;
	void DrawGrind();
	void MovePuttingObjectSelection();
	void MoveWaveMaxNumberSelection();
	void MoveWaveCurrentSelection();
	void DrawPuttingObjectSelectedName();
	void PutObject(Vector2 coor = Vector2(-1,-1));
	void EraseObject();
	LevelEditor();
	std::vector<std::string> config;
	std::vector<std::string> wavesConfig[nLevelWaves+1];
	void WriteConfig();
public:
	int itemOptionsWindowShowing;
	std::vector<int> itemOptionsIndex;
	OptionsBox itemOptions;
	void UpdateConfig();
	Level currentLevel;
	ObjectPlacer objectPlacer;
	std::vector<std::string> objectGroups;
	std::vector<std::string>::iterator ogSelected;
	void LoadLevel(Level* l, bool exists);
	void LoadLevelFromFile(std::string n);
	static LevelEditor instance;
	CameraBounds camBounds;
	Vector2 firstClick;
	Vector2 secondClick;
	static bool editting;
	void Update() override;
	void Draw() override;
	Vector2 GetTileCoorFromWorldPos(Vector2 p);
	void SetActive(bool b) override;
	void AfterStaticStart() override;
	bool hasMadeChanges;
	void MadeChange();
	void Save();
	void NewLevel(std::string n);

	void AddObject(Vector2 menuSpawnPos);
	void DeleteObject(Vector2 menuSpawnPos);
};

