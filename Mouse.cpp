#include "Mouse.h"

std::pair<int, int> Mouse::pos = std::pair(0,0);
int Mouse::asyncWheelY = 0;
bool Mouse::leftClickCheck = false;
bool Mouse::leftClickPressed = false;
bool Mouse::rightClickCheck = false;
bool Mouse::rightClickPressed = false;
bool Mouse::scrollUp = false;
bool Mouse::scrollDown = false;
std::future<void> asyncFuncMouseWheel = std::async(Mouse::ScrollDetection);
bool Mouse::isFileDropped;
std::string Mouse::fileDroppedDir;

void Mouse::Start() {
	SDL_StartTextInput();
}

void Mouse::Update() {
	leftClickPressed = false;
	if (SDL_GetMouseState(&pos.first, &pos.second) & SDL_BUTTON(1)) {
		if (!leftClickCheck) {
			leftClickPressed = true;
		}
		leftClickCheck = true;
	}
	else {
		leftClickCheck = false;
	}
	rightClickPressed = false;
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3)) {
		if (!rightClickCheck) {
			rightClickPressed = true;
		}
		rightClickCheck = true;
	}
	else {
		rightClickCheck = false;
	}

	if (asyncWheelY == -1 || Keyboard::KeyboardPressed(SDL_SCANCODE_UP)) {
		scrollDown = true;
		asyncWheelY = 0;
	}
	else {
		scrollDown = false;
	}

	if (asyncWheelY == 1 || Keyboard::KeyboardPressed(SDL_SCANCODE_DOWN)) {
		scrollUp = true;
		asyncWheelY = 0;
	}
	else {
		scrollUp = false;
	}
	

}

Vector2 Mouse::GetVector2Pos() {
	return Vector2(pos.first,pos.second);
}

Vector2 Mouse::GetVector2PosRef(Cam* c) {
	return ((GetVector2Pos() / Cam::currentCam->zoom + c->transform.position - ((SDLClass::GetScreenSizeVector2()/2) / Cam::currentCam->zoom)) );
}

void Mouse::ScrollDetection() {
	char* text = nullptr;
	char* composition;
	Sint32 cursor;
	Sint32 selection_len;
	while (true)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_MOUSEWHEEL)
			{
				asyncWheelY = event.wheel.y;
				
			}
			else if (event.type == SDL_TEXTINPUT)
			{
				Keyboard::textInputed = true;
				for (int i = 0; i < 32; i++)
					Keyboard::textInput[i] = event.text.text[i];

			}
			else if (event.type == SDL_DROPFILE) {   
				auto a = event.drop.file;
				isFileDropped = true;
				fileDroppedDir = std::string(a);
				SDL_free(a);  
			
			}
		}
	}
}

void Mouse::LateUpdate() {
	isFileDropped = false;
}