#include "InputManager.h"
bool InputManager::gamepad,
InputManager::up, InputManager::left, InputManager::down, InputManager::right,
InputManager::attack, InputManager::dash, InputManager::block,
InputManager::movup, InputManager::movleft, InputManager::movdown, InputManager::movright, InputManager::start, 
InputManager::back, InputManager::accept, InputManager::item;
SDL_GameController* InputManager::controller = nullptr;
bool InputManager::gamepadAttackPressed;
std::map<SDL_GameControllerButton, bool> InputManager::gamepadPressedButtons;
std::map<std::pair<SDL_GameControllerAxis, bool>, bool> InputManager::gamepadMovedAxis;

void InputManager::Start() {
	gamepadPressedButtons.insert(std::pair(SDL_CONTROLLER_BUTTON_X,false));
	gamepadPressedButtons.insert(std::pair(SDL_CONTROLLER_BUTTON_B, false));
	gamepadPressedButtons.insert(std::pair(SDL_CONTROLLER_BUTTON_A, false));
	gamepadPressedButtons.insert(std::pair(SDL_CONTROLLER_BUTTON_START, false));
	gamepadMovedAxis.insert(std::pair(std::pair(SDL_CONTROLLER_AXIS_LEFTY, false), false));
	gamepadMovedAxis.insert(std::pair(std::pair(SDL_CONTROLLER_AXIS_LEFTY ,true), false));
	gamepadMovedAxis.insert(std::pair(std::pair(SDL_CONTROLLER_AXIS_LEFTX, false), false));
	gamepadMovedAxis.insert(std::pair(std::pair(SDL_CONTROLLER_AXIS_LEFTX, true), false));
}

void InputManager::Update() {
	if(gamepad){
		int nj = SDL_NumJoysticks();
		Console::SendLineMessage(std::to_string(nj));
		if (nj < 1) {
			controller = nullptr;
		}
		else {
			if (!controller) {
				for (int i = 0; i < nj; ++i) {
					if (SDL_IsGameController(i)) {
						controller = SDL_GameControllerOpen(i);
					}
				}
			}
			int alx = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
			int aly = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
			int deadPoint = 15000;
			up = aly < -deadPoint;
			down = aly > deadPoint;
			left = alx < -deadPoint;
			right = alx > deadPoint;

			movup = AxisMoved(SDL_CONTROLLER_AXIS_LEFTY, false);
			movleft = AxisMoved(SDL_CONTROLLER_AXIS_LEFTX, false);
			movdown = AxisMoved(SDL_CONTROLLER_AXIS_LEFTY, true);
			movright = AxisMoved(SDL_CONTROLLER_AXIS_LEFTX, true);

			dash = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);
			attack = ButtonPressed(SDL_CONTROLLER_BUTTON_X);
			back = ButtonPressed(SDL_CONTROLLER_BUTTON_B);
			start = ButtonPressed(SDL_CONTROLLER_BUTTON_START);
			accept = ButtonPressed(SDL_CONTROLLER_BUTTON_A) || ButtonPressed(SDL_CONTROLLER_BUTTON_X);
		}
	}
	else {
		up = Keyboard::KeyboardCheck(SDL_SCANCODE_W);
		left = Keyboard::KeyboardCheck(SDL_SCANCODE_A);
		down = Keyboard::KeyboardCheck(SDL_SCANCODE_S);
		right = Keyboard::KeyboardCheck(SDL_SCANCODE_D);

		attack = Keyboard::KeyboardPressed(SDL_SCANCODE_SPACE);
		dash = Keyboard::KeyboardCheck(SDL_SCANCODE_LSHIFT);
		block = Keyboard::KeyboardCheck(SDL_SCANCODE_E);

		movup = Keyboard::KeyboardPressed(SDL_SCANCODE_W);
		movleft = Keyboard::KeyboardPressed(SDL_SCANCODE_A);
		movdown = Keyboard::KeyboardPressed(SDL_SCANCODE_S);
		movright = Keyboard::KeyboardPressed(SDL_SCANCODE_D);

		start = Keyboard::KeyboardPressed(SDL_SCANCODE_ESCAPE);
		back = Keyboard::KeyboardPressed(SDL_SCANCODE_ESCAPE);
		accept = Keyboard::KeyboardPressed(SDL_SCANCODE_SPACE) || Keyboard::KeyboardPressed(SDL_SCANCODE_RETURN);
		item = Keyboard::KeyboardPressed(SDL_SCANCODE_Q);
	}
}
bool InputManager::ButtonPressed(SDL_GameControllerButton b) {
	bool xpress = SDL_GameControllerGetButton(controller, b);
	bool r = xpress && !gamepadPressedButtons.at(b);
	gamepadPressedButtons.at(b) = xpress;
	return r;
}

bool InputManager::AxisMoved(SDL_GameControllerAxis b, bool dir) {
	int deadPoint = 15000;
	int al = SDL_GameControllerGetAxis(controller, b);
	bool xpress;
	if (dir) 
		xpress = al > deadPoint;
	else xpress = al < -deadPoint;
	bool r = xpress && !gamepadMovedAxis.at(std::pair(b,dir));
	gamepadMovedAxis.at(std::pair(b, dir)) = xpress;
	return r;
}
