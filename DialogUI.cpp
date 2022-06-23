#include "DialogUI.h"
DialogUI DialogUI::instance;

DialogUI::DialogUI() {
	inDialog = false;
	mouthSpeed = 6;
	effectSpeed = 6;
	effectSpeedCounter = effectSpeed;
}

void DialogUI::AfterStaticStart() {
	bg.Set("ui/bgDialog.png");
	flecha.Set("ui/flecha.png");

	bg.camDependent = false;
	flecha.camDependent = false;
	SpriteStatic::LoadAllSpritesInFolder(&charaPopUps,"ui/charapopups");

	effectChara[0].Set("ui/efecto01.png");
	effectChara[1].Set("ui/efecto02.png");
	effectIdle.Set("ui/efecto_idle.png");
	effectIdle.camDependent = false;
	effectChara[0].camDependent = false;
    effectChara[1].camDependent = false;


	
}

void DialogUI::Update() {
	if (inDialog) {
		
	}
}
void DialogUI::Draw() {
	if (inDialog) {

		

		if (Kang::gameTimeSpeed > 0) {
			if(dialogAudioTracker.isPaused())
				dialogAudioTracker.Resume();
			if (InputManager::attack) {
				PlayLine();
			}
		}
		else {
			if (!dialogAudioTracker.isPaused())
				dialogAudioTracker.Stop();
		}

		bg.Draw(Vector2(SDLClass::screenSizeX / 2, (SDLClass::screenSizeY / 10) * 8));
		effectIdle.Draw(Vector2((SDLClass::screenSizeX / 10) * (chara == "pm" ? 1.5 : (10 - 1.5)), (SDLClass::screenSizeY / 2) * .95), chara == "pm");
		
		if (!audioFileHasBeenPlayed) {
			audioFileHasBeenPlayed = true;
			dialogAudioTracker.Stop();
			dialogAudioTracker.TryToTrack("dialog/" + audiofile, &Audio::instance.voice);
			tb.AddText(line);
		}

		if (dialogAudioTracker.isPlaying()) {

			mouthSpeedCounter -= Kang::gameTimeSpeed;
			if (mouthSpeedCounter <= 0) {
				mouthOpen = !mouthOpen;
				mouthSpeedCounter = mouthSpeed;
			}
		}
		else {
			flecha.Draw(Vector2((SDLClass::screenSizeX / 8) * 7, (SDLClass::screenSizeY / 10) * 9));
			mouthOpen = 0;
		}
		charaPopUps.at(chara + std::to_string((1 + (int)mouthOpen))).
			Draw(Vector2((SDLClass::screenSizeX / 10) * (chara == "pm" ? 1.5 : (10 - 1.5)), (SDLClass::screenSizeY / 2) * .95), chara == "pm");
		auto rp = Vector2((SDLClass::screenSizeX / 12) * (chara == "pm" ? 4 : 2), (SDLClass::screenSizeY / 10) * 7);
		tb.pos = rp;
		Rect r = Rect(bg.spriteRect.p1, bg.spriteRect.p2);
		tb.originalMarkRect = Rect(r.w / 12 * 7, r.h / 12 * 7);
		tb.Write(Kang::gameTimeSpeed);
		tb.Draw();

		
	}

	if (popUpCounter > 0) {

		effectSpeedCounter -= Kang::gameTimeSpeed;
		if (effectSpeedCounter <= 0) {
			effectState = !effectState;
			effectSpeedCounter = effectSpeed;
		}
		

		effectChara[effectState].Draw(Vector2(SDLClass::screenSizeX * .06, SDLClass::screenSizeY  * .85), true, 0, SDL_Rect(), .33);
		popUpCounter -= Kang::gameTimeSpeed;
		charaPopUps.at(popUpChara + std::to_string(2)).
			Draw(Vector2(SDLClass::screenSizeX * .06, SDLClass::screenSizeY * .85), true, 0, SDL_Rect(), .33);
	}
}

void DialogUI::StartDialog(std::string n) {
	//gotta move this shit
	Rect r = Rect(bg.spriteRect.p1, bg.spriteRect.p2);
	tb = WriteTextBox(Vector2(), Rect(r.w / 12 * 7, r.h / 12 * 7));
	auto rp = Vector2((SDLClass::screenSizeX / 12) * 4, (SDLClass::screenSizeY / 10) * 7);
	tb.pos = rp;
	tb.displayText = Text("", 40, Color(0), "altehaas");
	tb.camDependent = false;
	//eeee

	inDialog = true;
	currentDialog = &dialogManager.dialogs.at(n);
	currentDialogLine = 0;
	PlayLine();
}

void DialogUI::StartPopUp(std::string puc, float popupTime) {
	popUpChara = puc;
	popUpCounter = popupTime;
}

void DialogUI::PlayLine() {
	if (currentDialogLine == currentDialog->dialoglines.size())
		inDialog = false;
	else {
		audioFileHasBeenPlayed = false;
		auto& dl = currentDialog->dialoglines[currentDialogLine];
		line = dl.dLine;
		chara = dl.chara;
		audiofile = dl.audiofile;
		currentDialogLine++;
	}
	
}