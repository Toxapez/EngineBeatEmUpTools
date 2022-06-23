#include "FrameController.h"

const int FrameController::FPS = 60;
const int FrameController::frameDelay = 1000 / FPS;
Uint32 FrameController::framestart;
int FrameController::frametime;

void FrameController::FirstUpdate() {
	framestart = SDL_GetTicks();
}

void FrameController::LateUpdate() {
	frametime = SDL_GetTicks() - framestart;

	if (frameDelay > frametime) {
		SDL_Delay(frameDelay - frametime);
	}
	SDL_Event evt;
	SDL_PollEvent(&evt);
}