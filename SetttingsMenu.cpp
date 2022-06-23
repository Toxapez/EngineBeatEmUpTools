#include "SetttingsMenu.h"

std::map<std::string, SpriteStatic> SettingsMenu::spritesSM;
SettingsMenu SettingsMenu::instance;


SettingsMenu::SettingsMenu() {
	nOptions = 6;
	resolutionsList.push_back(Vector2(640, 360));
	resolutionsList.push_back(Vector2(960, 540));
	resolutionsList.push_back(Vector2(1280, 720));
	resolutionsList.push_back(Vector2(1920, 1080));
	resolutionsList.push_back(Vector2(2560, 1440));
	resolutionsList.push_back(Vector2(3840, 2160));
}

void SettingsMenu::AfterStaticStart() {
	SpriteStatic::LoadAllSpritesInFolder(&spritesSM, "ui/menus/settings");
	
}

void SettingsMenu::Update() {

	if (InputManager::movdown) {
		optionSelected++;
		if (optionSelected == nOptions)
			optionSelected = 0;
	}
	else if (InputManager::movup) {
		if (optionSelected == 0)
			optionSelected = nOptions;
		optionSelected--;
	}

	

	if (optionSelected == 0) {
		float a = Audio::instance.music.engine->getSoundVolume();
		if (InputManager::right && Audio::instance.music.engine->getSoundVolume() < 1)
			Audio::instance.music.engine->setSoundVolume(Audio::instance.music.engine->getSoundVolume() +.01);
		else if (InputManager::left && Audio::instance.music.engine->getSoundVolume() > 0)
			Audio::instance.music.engine->setSoundVolume(Audio::instance.music.engine->getSoundVolume() - .01);
	}
	if (optionSelected == 1) {
		if (InputManager::right && Audio::instance.sfx.engine->getSoundVolume() < 1)
			Audio::instance.sfx.engine->setSoundVolume(Audio::instance.sfx.engine->getSoundVolume() + .01);
		else if (InputManager::left && Audio::instance.sfx.engine->getSoundVolume() > 0)
			Audio::instance.sfx.engine->setSoundVolume(Audio::instance.sfx.engine->getSoundVolume() - .01);
	}
	if (optionSelected == 2) {
		if (InputManager::right && Audio::instance.voice.engine->getSoundVolume() < 1)
			Audio::instance.voice.engine->setSoundVolume(Audio::instance.voice.engine->getSoundVolume() + .01);
		else if (InputManager::left && Audio::instance.voice.engine->getSoundVolume() > 0)
			Audio::instance.voice.engine->setSoundVolume(Audio::instance.voice.engine->getSoundVolume() - .01);
	}
	if (optionSelected == 3) {
		//controles
		if (InputManager::movleft || InputManager::movright)
			InputManager::gamepad = !InputManager::gamepad;
	}
	if (optionSelected == 4) {
		if (InputManager::movleft || InputManager::movright) {
			if (InputManager::movleft) {
				if (resSelected == 0)
					resSelected = resolutionsList.size();
				resSelected--;
			}
			else if (InputManager::movright){
				resSelected++;
				if (resSelected == resolutionsList.size())
					resSelected = 0;
			}
			SDLClass::ChangeWindowSize(resolutionsList[resSelected].x, resolutionsList[resSelected].y);
		}
	}
	if (optionSelected == 5) {
		if (InputManager::left) {
			if (Being::minimunShutTime < Meth::SegToFrame(10))
				Being::minimunShutTime += 3;
		}
		else if (InputManager::right) {
			if (Being::minimunShutTime > 3)
				Being::minimunShutTime -= 3;
			
		}
		
	}

	if (InputManager::movleft || InputManager::movright)
		SaveSettings();

	if(InputManager::back) {
		Close();
		menus[0]->Open();
	}
	
}

void SettingsMenu::SaveSettings() {
	std::ofstream file("settings.config");
	if (file.is_open())
	{
		
		file << std::to_string((int)(100 * Audio::instance.music.engine->getSoundVolume())) << "\n";
		file << std::to_string((int)(100 * Audio::instance.sfx.engine->getSoundVolume())) << "\n";
		file << std::to_string((int)(100 * Audio::instance.voice.engine->getSoundVolume())) << "\n";
		file << std::to_string(int(InputManager::gamepad)) << "\n";
		file << std::to_string(resSelected) << "\n";
		file << std::to_string((int)(100 * Being::minimunShutTime)) << "\n";

		file.close();
		
	}
}

void SettingsMenu::LoadSettings() {
	std::ifstream file("settings.config");
	if (file)
	{
		std::string str;
		getline(file, str);
		Audio::instance.music.engine->setSoundVolume((float)stoi(str) / 100);
		getline(file, str);
		Audio::instance.sfx.engine->setSoundVolume((float)stoi(str) / 100);
		getline(file, str);
		Audio::instance.voice.engine->setSoundVolume((float)stoi(str) / 100);
		getline(file, str);
		InputManager::gamepad = stoi(str);
		getline(file, str);
		resSelected = stoi(str);
		getline(file, str);
		Being::minimunShutTime = (float)stoi(str) / 100;

		SDLClass::ChangeWindowSize(resolutionsList[resSelected].x, resolutionsList[resSelected].y);
	}
}

void SettingsMenu::Draw() {
	float slider1f = Audio::instance.music.engine->getSoundVolume();
	float slider2f = Audio::instance.sfx.engine->getSoundVolume();
	float slider3f = Audio::instance.voice.engine->getSoundVolume();
	bool controllerSelection = !InputManager::gamepad;
	std::string resString = std::to_string(SDLClass::screenSizeX) + "x" + std::to_string(SDLClass::screenSizeY);
	float slider6f = 1.0 - ((float)Meth::FrameToSeg(Being::minimunShutTime) / 10);

	Vector2 originPos = Vector2(0, SDLClass::screenSizeY * scroll);
	float windowY = 2;
	windowSpr->Draw((SDLClass::GetScreenSizeVector2() / 2) + originPos + Vector2(0, (windowSpr->GetSize().y / 4) * windowY), true, 0, SDL_Rect(), 1, Vector2(1.2, windowY));
	Vector2 titlepos = Vector2(SDLClass::screenSizeX / 2, SDLClass::screenSizeY * .2) + originPos;
	titleSpr->Draw(titlepos);
	TextDrawer::DrawSimpleText(Text("Ajustes", 54, Color(0), "altehaas", false), titlepos);

	Text t[4];
	t[0] = Text("Sonido", 38, Color(0), "altehaas", false);
	t[1] = Text("Control", 38, Color(0), "altehaas", false);
	t[2] = Text("Graficos", 38, Color(0), "altehaas", false);
	t[3] = Text("Juego", 38, Color(0), "altehaas", false);

	//titulos
	TextDrawer::DrawSimpleText(t[0], originPos + Vector2(SDLClass::screenSizeX / 2, SDLClass::screenSizeY * .325));
	TextDrawer::DrawSimpleText(t[1], originPos + Vector2(SDLClass::screenSizeX / 2, SDLClass::screenSizeY * .675));
	TextDrawer::DrawSimpleText(t[2], originPos + Vector2(SDLClass::screenSizeX / 2, SDLClass::screenSizeY * .975));
	TextDrawer::DrawSimpleText(t[3], originPos + Vector2(SDLClass::screenSizeX / 2, SDLClass::screenSizeY * 1.2));

	float sepaIcon = SDLClass::screenSizeX * .01;
	//sound settings
	Vector2 epos1 = originPos + Vector2(SDLClass::screenSizeX / 2, SDLClass::screenSizeY * .4);
	sliderBarSpr->Draw(Vector2(epos1.x + icon1->GetSize().x / 2, epos1.y));
	icon1->Draw(Vector2(epos1.x - (sliderBarSpr->GetSize().x / 2 + sepaIcon), epos1.y));
	
	sliderSpr->Draw(Vector2(((epos1.x + icon1->GetSize().x / 2) - sliderBarSpr->GetSize().x / 2)
		+ sliderBarSpr->GetSize().x * slider1f, epos1.y));


	Vector2 epos2 = originPos + Vector2(SDLClass::screenSizeX / 2, SDLClass::screenSizeY * .5);
	sliderBarSpr->Draw(Vector2(epos2.x + icon2->GetSize().x / 2, epos2.y));
	icon2->Draw(Vector2(epos2.x - (sliderBarSpr->GetSize().x / 2 + sepaIcon), epos2.y));

	sliderSpr->Draw(Vector2(((epos2.x + icon2->GetSize().x / 2) - sliderBarSpr->GetSize().x / 2)
		+ sliderBarSpr->GetSize().x * slider2f, epos2.y));


	Vector2 epos3 = originPos + Vector2(SDLClass::screenSizeX / 2, SDLClass::screenSizeY * .6);
	sliderBarSpr->Draw(Vector2(epos3.x + icon3->GetSize().x / 2, epos3.y));
	icon3->Draw(Vector2(epos3.x - (sliderBarSpr->GetSize().x / 2 + sepaIcon), epos3.y));

	sliderSpr->Draw(Vector2(((epos3.x + icon3->GetSize().x / 2) - sliderBarSpr->GetSize().x / 2)
		+ sliderBarSpr->GetSize().x * slider3f, epos3.y));

	//controles
	Vector2 epos4 = originPos + Vector2(SDLClass::screenSizeX / 2, SDLClass::screenSizeY * .8);
	float sepa1 = .1 * SDLClass::screenSizeX;
	icon4->Draw(Vector2(epos4.x - sepa1 / 2, epos4.y));
	icon5->Draw(Vector2(epos4.x + sepa1 / 2, epos4.y));
	iconSelector->Draw(Vector2(epos4.x + (sepa1 / 2) * (controllerSelection ? 1 : -1), epos4.y));

	//graficos 
	Vector2 epos5 = originPos + Vector2(SDLClass::screenSizeX / 2, SDLClass::screenSizeY * 1.05);
	float sepa2 = .02 * SDLClass::screenSizeX;
	Text resT = Text(resString, 64, Color(0), "altehaas", false);
	icon6->Draw(Vector2(epos5.x - (resT.GetSize().x / 2 + sepa2 / 2), epos5.y));
	TextDrawer::DrawSimpleText(resT, epos5 + Vector2(icon6->GetSize().x / 2 + sepa2 / 2, 0));

	//juego
	Vector2 epos6 = originPos + Vector2(SDLClass::screenSizeX / 2, SDLClass::screenSizeY * 1.3);
	sliderBarSpr->Draw(Vector2(epos6.x + icon7->GetSize().x / 2, epos6.y));
	icon7->Draw(Vector2(epos6.x - (sliderBarSpr->GetSize().x / 2 + sepaIcon), epos6.y));

	sliderSpr->Draw(Vector2(((epos6.x + icon7->GetSize().x / 2) - sliderBarSpr->GetSize().x / 2)
		+ sliderBarSpr->GetSize().x * slider6f, epos6.y));

	//selection
	Vector2 tpos[6];
	tpos[0] = Vector2(icon1->GetSize().x + sliderBarSpr->GetSize().x + sepaIcon, epos1.y);
	tpos[1] = Vector2(icon2->GetSize().x + sliderBarSpr->GetSize().x + sepaIcon, epos2.y);
	tpos[2] = Vector2(icon3->GetSize().x + sliderBarSpr->GetSize().x + sepaIcon, epos3.y);
	tpos[3] = Vector2(icon4->GetSize().x + icon5->GetSize().x + sepa1, epos4.y);
	tpos[4] = Vector2(icon6->GetSize().x + resT.GetSize().x + sepa2, epos5.y);
	tpos[5] = Vector2(icon7->GetSize().x + sliderBarSpr->GetSize().x + sepaIcon, epos6.y);

	selectorSpr->Draw(Vector2((SDLClass::screenSizeX / 2) - ((tpos[optionSelected].x) / 2 + selectorSpr->size.x), tpos[optionSelected].y));
	selectorSpr->Draw(Vector2((SDLClass::screenSizeX / 2) + ((tpos[optionSelected].x) / 2 + selectorSpr->size.x), tpos[optionSelected].y), false);

	if (tpos[optionSelected].y > SDLClass::screenSizeY * .6) {
		scroll -= tpos[optionSelected].y > SDLClass::screenSizeY * .61 ? abs(tpos[optionSelected].y - SDLClass::screenSizeY * .6)* .00003 : .0005;
	}
	else if (tpos[optionSelected].y < SDLClass::screenSizeY * .4) {
		scroll += tpos[optionSelected].y < SDLClass::screenSizeY * .39 ? abs(tpos[optionSelected].y - SDLClass::screenSizeY * .4) * .00003 : .0005;
	}


}

void SettingsMenu::Open() {
	isActive = true;
	isOpen = true;
	optionSelected = 0;
	windowSpr = &Menu::sprites.at("window");
	titleSpr = &Menu::sprites.at("title");
	icon1 = &spritesSM.at("musicicon");
	icon2 = &spritesSM.at("sfxicon");
	icon3 = &spritesSM.at("voiceicon");
	icon4 = &spritesSM.at("controllericon");
	icon5 = &spritesSM.at("keyboardicon");
	icon6 = &spritesSM.at("resicon");
	icon7 = &spritesSM.at("faicon");
	selectorSpr = &Menu::sprites.at("selector");
	sliderSpr = &Menu::sprites.at("slider");
	sliderBarSpr = &Menu::sprites.at("sliderbar");
	iconSelector = &Menu::sprites.at("iconselector");
	scroll = 0;
}
void SettingsMenu::Close() {
	isActive = false;
	isOpen = false;

}