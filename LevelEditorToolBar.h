#pragma once
#include "ButtonUI.h"
#include "TextUI.h"
#include "WindowUI.h"
#include "LevelEditor.h"
#include "UIBar.h"
#include "BGItemsCreator.h"

class LevelEditorToolBar : public GameObject
{
	static LevelEditorToolBar instance;
	WindowUI wUI;
	WindowUIComponent wUIC;
	UIBar uiBar;
	
	ButtonUI addObjectButton;
	ButtonUI deleteObjectButton;
	ButtonUI createObjectButton;

	TextUI addObjectText;
	TextUI deleteObjectText;
	TextUI createObjectText;
	BGItemsCreator bgItemsCreator;

	LevelEditorToolBar();
	void AfterStaticStart();
	void Update();
	void Draw();

	Vector2 standardButtonSize;

};

