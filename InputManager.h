#pragma once
#include "Keyboard.h"
#include "Console.h"
#include <string>

struct InputManager
{
	static bool gamepad,
		up, left, down, right, 
		attack, dash, block,
		movup, movleft, movdown, movright, start, back, accept, item;
	static SDL_GameController* controller;
	static bool gamepadAttackPressed;
	static std::map<SDL_GameControllerButton, bool> gamepadPressedButtons;
	static std::map<std::pair<SDL_GameControllerAxis,bool>, bool> gamepadMovedAxis;
	static void Start();
	static void Update();
	static bool ButtonPressed(SDL_GameControllerButton b);
	static bool AxisMoved(SDL_GameControllerAxis b, bool dir);
};

