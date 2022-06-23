#include "BGItemsCreator.h"

BGItemsCreator::BGItemsCreator() {
	
}

void BGItemsCreator::AfterStaticStart() {
	title.Set(Vector2(), Vector2(350, 50));
	title.text = "BG Item Creator";
	closeButton.Set(Vector2(), Vector2(50, 50));
	closeButton.icon = &closeText;
	closeText.Set(Vector2(), Vector2(50, 50));
	closeText.text = "CLOSE";

	topBar.AddPart(&title);
	topBar.AddPart(&closeButton);

	nameInstructions.Set(Vector2(), Vector2(180, 40));
	nameInstructions.text = "Insert name:";
	nameInput.Set(Vector2(), Vector2(400, 30));

	spriteInstructions.Set(Vector2(), Vector2(180, 40));
	spriteInstructions.text = "Insert sprite:";
	spriteInput.Set(Vector2(), Vector2(400, 80));

	boxInstructions.Set(Vector2(), Vector2(80, 30));
	boxInstructions.text = "Set OffSet:";
	boxInput.Set(Vector2(), Vector2(400, 400));
	boxInput.mode = 2;

	doneButton.Set(Vector2(), Vector2(150, 50));
	doneButton.icon = &doneText;
	doneText.Set(Vector2(), Vector2(150, 50));
	doneText.text = "DONE";

	wUIC.AddPart(&topBar);
	wUIC.AddPart(&nameInstructions);
	wUIC.AddPart(&nameInput);
	wUIC.AddPart(&spriteInstructions);
	wUIC.AddPart(&spriteInput);
	wUIC.AddPart(&boxInstructions);
	wUIC.AddPart(&boxInput);
	wUIC.AddPart(&doneButton);

	wUI.AddComponent(&wUIC);

	SetActive(false);
}

void BGItemsCreator::Update() {

	if (nameInput.hasMadeChange) {
		nameInput.hasMadeChange = false;
		bool happen = false;
		if (!nameInput.text.empty()) {
			if (!FileUtilities::FileExist((std::string("assets/sprites/bg/") + nameInput.text + ".png").c_str())) {
				nameInput.outLineColor = Color(0, 255, 0);
				nameInput.color = Color(240, 255, 240);
				nameCorrect = true;
				happen = true;
			}
			
		}
		if(!happen){
			nameInput.outLineColor = Color(255, 0, 0);
			nameInput.color = Color(255, 240, 240);
			nameCorrect = false;
		}
	}

	if (spriteInput.hasMadeChange) {
		if (!spriteInput.dir.empty()) {
			boxInput.enabled = true;
			sprTemp.ForcedSet(spriteInput.dir);
			sprTemp.ExternalLoad();
			boxInput.texture = &sprTemp;
			spriteCorrect = true;
		}
		else {
			boxInput.boxCatched = Rect();
			boxInput.enabled = false;
			sprTemp.Clear();
			boxInput.texture = nullptr;
			spriteCorrect = false;
		}
	}

	doneButton.enabled = spriteCorrect && nameCorrect;
	
	if (doneButton.pressed) {
		NewPlaceableObjectsCreator::BGItem(nameInput.text, spriteInput.dir, boxInput.offset);
		nameCorrect = false;
		spriteCorrect = false;
		boxInput.Clear();
		sprTemp.Clear();
		spriteInput.Clear();
		nameInput.Clear();
	}

	if (closeButton.pressed) {
		SetActive(false);
	}


	wUI.transform.position = transform.position;
}
void BGItemsCreator::Draw() {
	
}

void BGItemsCreator::SetActive(bool b) {
	wUI.SetActive(b);
	isActive = b;
	if (b) {
		nameCorrect = false;
		spriteCorrect = false;

		boxInput.enabled = false;
	}
}
