#include "Keyboard.h"


SDL_Event Keyboard::event;
const Uint8* Keyboard::keyboard_state_array = SDL_GetKeyboardState(NULL);
std::map <SDL_Scancode, bool> Keyboard::keyboard_pressed_map;
std::map <SDL_Scancode, bool> Keyboard::keyboard_pressed_last_map;
bool Keyboard::textInputed = false;
char Keyboard::textInput[32];
bool Keyboard::normalInputActive = true;

bool Keyboard::KeyboardCheck(SDL_Scancode _k) {
	bool r = false;
	if (keyboard_state_array[_k]) {
		r = true;
		keyboard_pressed_map[_k] = true;
	}
	return r && normalInputActive;
}
bool Keyboard::KeyboardPressed(SDL_Scancode _k) {
	bool r = false;
	if (keyboard_state_array[_k] && !keyboard_pressed_last_map[_k]) {
		r = true;
		keyboard_pressed_map[_k] = true;
	}
	return r && normalInputActive;
}

bool Keyboard::KeyboardFirstPressed(SDL_Scancode _k) {
	bool r = false;
	if(keyboard_pressed_map[_k])
		return false;
	if (keyboard_state_array[_k] && !keyboard_pressed_last_map[_k]) {
		r = true;
		keyboard_pressed_map[_k] = true;
	}
	return r && normalInputActive;
}

void Keyboard::UpdatePressedKeys() {

	keyboard_pressed_last_map = keyboard_pressed_map;

	for (auto& c : keyboard_pressed_map) {
		if (!keyboard_state_array[c.first]) {
			c.second = false;
		}
	}
}

void Keyboard::LateUpdate() {
	UpdatePressedKeys();
	textInputed = false;
	
}

std::string Keyboard::GetInputText() {
	return std::string(textInput);
}