#include "LevelEditorToolBar.h"


LevelEditorToolBar LevelEditorToolBar::instance;

LevelEditorToolBar::LevelEditorToolBar() {
	standardButtonSize = Vector2(100, 100);
	camDependent = false;
}

void LevelEditorToolBar::AfterStaticStart() {
	//Add and delete
	addObjectButton.Set(Vector2(), Rect(standardButtonSize));
	deleteObjectButton.Set(Vector2(), Rect(standardButtonSize));

	addObjectText.Set(Vector2(), Rect(standardButtonSize));
	deleteObjectText.Set(Vector2(), Rect(standardButtonSize));

	addObjectText.text = "ADD OBJECT Shortcut: I";
	deleteObjectText.text = "DELETE OBJECT Shortcut: I + ALT";

	addObjectButton.icon = &addObjectText;
	deleteObjectButton.icon = &deleteObjectText;

	uiBar.AddPart(&addObjectButton);
	uiBar.AddPart(&deleteObjectButton);
	uiBar.AddPart(&createObjectButton);

	wUIC.AddPart(&uiBar);

	wUI.AddComponent(&wUIC);

	//Create
	createObjectButton.Set(Vector2(), Rect(standardButtonSize));
	createObjectText.Set(Vector2(), Rect(standardButtonSize));
	createObjectButton.icon = &createObjectText;

}

void LevelEditorToolBar::Update() {

	auto lvE = &LevelEditor::instance;

	if (lvE->isActive && lvE->editting) {
		if (!wUI.isActive)
			wUI.SetActive(true);

		transform.position = Cam::currentCam->transform.position;
		transform.position.y += SDLClass::GetScreenSizeVector2().y / 2 - (standardButtonSize.y);

		wUI.transform.position = transform.position;

		if (addObjectButton.pressed)
			lvE->AddObject(Cam::currentCam->transform.position);

		if (deleteObjectButton.pressed)
			lvE->DeleteObject(Cam::currentCam->transform.position);


		if ((*lvE->ogSelected) == "Background") {
			createObjectText.text = "CREATE OBJECT";
			createObjectButton.enabled = true;
			createObjectText.color = Color(255);
			if (createObjectButton.pressed) {
				bgItemsCreator.SetActive(true);
				bgItemsCreator.transform.position = Cam::currentCam->transform.position;
			}

		}
		else {
			createObjectText.text = "CREATE OBJECT Disable";
			createObjectButton.enabled = false;
			createObjectText.color = Color(155);
		}
	}
	else {
		if (wUI.isActive)
			wUI.SetActive(false);
	}

	
}
void LevelEditorToolBar::Draw() {

}