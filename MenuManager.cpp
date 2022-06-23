#include "MenuManager.h"
MenuManager MenuManager::instance;

void MenuManager::AfterStaticStart() {
	SpriteStatic::LoadAllSpritesInFolder(&Menu::sprites, "ui/menus/general");
	Menu::menus.push_back(&PauseMenu::instance);
	Menu::menus.push_back(&SettingsMenu::instance);

	SettingsMenu::instance.LoadSettings();
}
void MenuManager::Update() {
	if (Menu::menuManagerIsActive) {
		if (InputManager::start) {
			PauseMenu::instance.Open();
			Menu::menuManagerIsActive = false;
			Kang::gameTimeSpeed = 0;
			InputManager::start = false;
			InputManager::back = false;
		}
		
	}
}