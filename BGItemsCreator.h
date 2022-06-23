#pragma once
#include "WindowUI.h"
#include "FileCatcher.h"
#include "InputTextBox.h"
#include "TextUI.h"
#include "ButtonUI.h"
#include "BoxCatcherUI.h"
#include "UIBar.h"
#include "NewPlaceableObjectsCreator.h"

struct BGItemsCreator : public GameObject
{
	WindowUI wUI;
	WindowUIComponent wUIC;

	UIBar topBar;
	TextUI title;
	ButtonUI closeButton;
	TextUI closeText;

	TextUI nameInstructions;
	InputTextBox nameInput;

	TextUI spriteInstructions;
	FileCatcher spriteInput;
	SpriteStatic sprTemp;

	TextUI boxInstructions;
	BoxCatcherUI boxInput;

	ButtonUI doneButton;
	TextUI doneText;


	bool nameCorrect;
	bool spriteCorrect;

	BGItemsCreator();
	void AfterStaticStart();
	void Update();
	void Draw();
	void SetActive(bool b);

};

