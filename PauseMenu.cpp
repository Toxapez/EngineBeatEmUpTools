#include "PauseMenu.h"
PauseMenu PauseMenu::instance;

PauseMenu::PauseMenu() {
	nOptions = 3;
}

void PauseMenu::Update() {

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

	if (InputManager::accept) {
		InputManager::attack = false;
		if (optionSelected == 0) {
			Close();
			Kang::gameTimeSpeed = 1;
			Menu::menuManagerIsActive = true;
		}
		if (optionSelected == 1) {
			Close();
			menus[1]->Open();
		}
		if (optionSelected == 2) {
			
		}
	}
	if (InputManager::back) {
		Close();
		Kang::gameTimeSpeed = 1;
		Menu::menuManagerIsActive = true;
	}
}
void PauseMenu::Draw() {
	windowSpr->Draw(SDLClass::GetScreenSizeVector2() / 2,true,0,SDL_Rect(),1,Vector2(.7,.8));
	Vector2 titlepos = Vector2(SDLClass::screenSizeX / 2, SDLClass::screenSizeY * .2);
	titleSpr->Draw(titlepos);
	TextDrawer::DrawSimpleText(Text("Pausa",54,Color(0),"altehaas",false),titlepos);

	
	Text t[3];
	t[0] = Text("Continuar", 54, Color(0), "altehaas", false);
	t[1] = Text("Opciones", 54, Color(0), "altehaas", false);
	t[2] = Text("Salir", 54, Color(0), "altehaas", false);

	float s[3];
	s[0] = t[0].GetSize().x + icon1->GetSize().x*1.3;
	s[1] = t[1].GetSize().x + icon2->GetSize().x*1.3;
	s[2] = t[2].GetSize().x + icon3->GetSize().x*1.3;

	Vector2 tpos[3];
	tpos[0] = Vector2((SDLClass::screenSizeX / 2) +  icon1->GetSize().x*1.3/ 2, SDLClass::screenSizeY * .4);
	tpos[1] = Vector2((SDLClass::screenSizeX / 2) +  icon2->GetSize().x*1.3/ 2, SDLClass::screenSizeY * .55);
	tpos[2] = Vector2((SDLClass::screenSizeX / 2) +  icon3->GetSize().x*1.3/2, SDLClass::screenSizeY * .7);


	

	icon1->Draw(Vector2((SDLClass::screenSizeX / 2) - t[0].GetSize().x / 2, tpos[0].y), true, optionSelected == 0 ? -.15 : 0, SDL_Rect(), optionSelected == 0 ? 1.25 : 1);
	icon2->Draw(Vector2((SDLClass::screenSizeX / 2) - t[1].GetSize().x / 2, tpos[1].y), true, optionSelected == 1 ? -.15 : 0, SDL_Rect(), optionSelected == 1 ? 1.25 : 1);
	icon3->Draw(Vector2((SDLClass::screenSizeX / 2) - t[2].GetSize().x /2, tpos[2].y), true, optionSelected == 2 ? -.15 : 0, SDL_Rect(), optionSelected == 2 ? 1.25 : 1);
	float a = t[0].GetSize().x;
	TextDrawer::DrawSimpleText(t[0], tpos[0]);
	TextDrawer::DrawSimpleText(t[1], tpos[1]);
	TextDrawer::DrawSimpleText(t[2], tpos[2]);


	selectorSpr->Draw(Vector2((SDLClass::screenSizeX / 2) - ((s[optionSelected])/2 + selectorSpr->size.x), tpos[optionSelected].y));
	selectorSpr->Draw(Vector2((SDLClass::screenSizeX / 2) + ((s[optionSelected])/2 + selectorSpr->size.x), tpos[optionSelected].y), false);
	
}
void PauseMenu::Open() {
	isActive = true;
	isOpen = true;
	optionSelected = 0;
	windowSpr = &Menu::sprites.at("window");
	titleSpr = &Menu::sprites.at("title");
	icon1 = &Menu::sprites.at("back");
	icon2 = &Menu::sprites.at("settings");
	icon3 = &Menu::sprites.at("exit");
	selectorSpr = &Menu::sprites.at("selector");
}
void PauseMenu::Close() {
	isActive = false;
	isOpen = false;
	
}
