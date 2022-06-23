#pragma once
#include <map>
#include "SDLClass.h"
#include "Console.h"
class Keyboard
{
	static SDL_Event event;
	static const Uint8* keyboard_state_array;
	static std::map <SDL_Scancode, bool> keyboard_pressed_map;
	static std::map <SDL_Scancode, bool> keyboard_pressed_last_map;
	static void UpdatePressedKeys();
public:
	static bool KeyboardCheck(SDL_Scancode _k);
	static bool KeyboardPressed(SDL_Scancode _k);
	static bool KeyboardFirstPressed(SDL_Scancode _k);
	static std::string GetInputText();
	static void LateUpdate();
	static bool textInputed;
	static char textInput[32];
	static bool normalInputActive;
};

