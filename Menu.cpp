#include "Menu.h"
std::map<std::string, SpriteStatic> Menu::sprites;
bool Menu::menuManagerIsActive = true;
std::vector<Menu*> Menu::menus;

Menu::Menu() {
	isActive = false;
	isOpen = false;
	layer = 11;
}

void Menu::Open() {

}
void Menu::Close() {

}