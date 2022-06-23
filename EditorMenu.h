#pragma once
#include "LevelEditor.h"
#include "OptionsBox.h"
#include "EmergentMessage.h"
#include "BooleanQuestion.h"
class EditorMenu : public GameState
{
	static EditorMenu instance;
	EditorMenu();
	void Update() override;
	void Draw() override;
	void SetActive(bool b) override;
	std::vector<std::pair<std::string,std::filesystem::directory_entry>> levels;
	OptionsBox levelOptions;
	OptionsBox generalOptions;
	Cam cam;
	CameraBounds editorMCameraBounds;
	void ReadLevels();
	void AfterStaticStart() override;
};