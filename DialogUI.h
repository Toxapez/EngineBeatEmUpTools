#pragma once
#include "DialogManager.h"
#include "SpriteStatic.h"
#include <map>
#include "Audio.h"
#include "WriteTextBox.h"
#include "InputManager.h"

struct DialogUI : public GameObject
{
	DialogManager dialogManager;
	void Update() override;
	void Draw() override;
	DialogUI();
	static DialogUI instance;

	std::map<std::string, SpriteStatic> charaPopUps;
	SpriteStatic bg;
	void AfterStaticStart();
	SpriteStatic flecha;
	SpriteStatic effectChara[2];
	SpriteStatic effectIdle;
	Dialog* currentDialog;
	void StartDialog(std::string n);
	bool inDialog;
	int currentDialogLine;
	void PlayLine();
	std::string line;
	std::string chara;
	bool audioFileHasBeenPlayed;
	std::string audiofile;
	AudioTracker dialogAudioTracker;
	bool mouthOpen;
	float mouthSpeed;
	float mouthSpeedCounter;
	bool effectState;
	float effectSpeed;
	float effectSpeedCounter;
	WriteTextBox tb;
	float popUpCounter;
	std::string popUpChara;
	void StartPopUp(std::string puc, float popupTime = Meth::SegToFrame(.9));
};

