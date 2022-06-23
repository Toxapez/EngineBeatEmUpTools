#include "Cam.h"
Cam* Cam::currentCam = nullptr;

Cam::Cam() {
	zoom = 1;
	rotation = 0;
	speed = 1;
	layer = 20;
}

Cam::Cam(Vector2 pos) {
	transform.position = pos;
	zoom = 1;
	rotation = 0;
}

void Cam::SetCamMovible(Vector2 pos, float s, CameraBounds* cb) {
	transform.position = pos;
	speed = s;
	cameraBounds = cb;

}

void Cam::Update() {
	if (move) {
		if (Keyboard::KeyboardCheck(SDL_SCANCODE_W)) {
			transform.position += Vector2(0, -speed);
		}
		if (Keyboard::KeyboardCheck(SDL_SCANCODE_A)) {
			transform.position += Vector2(-speed, 0);
		}
		if (!Keyboard::KeyboardCheck(SDL_SCANCODE_LCTRL)) {
			if (Keyboard::KeyboardCheck(SDL_SCANCODE_S)) {
				transform.position += Vector2(0, speed);
			}
		}
		if (Keyboard::KeyboardCheck(SDL_SCANCODE_D)) {
			transform.position += Vector2(speed, 0);
		}
	}

	worldZoom = 0;
	if (zoomAnimation) {
		zoomAnimationCounter += Kang::gameTimeSpeed;

		if (zoomAnimationTime / 2 >= zoomAnimationCounter)
			zoomAnimationQuantity = zoomAnimationTarget * (zoomAnimationCounter / (zoomAnimationTime / 2));
		else
			zoomAnimationQuantity = -1 * (zoomAnimationTarget * ((zoomAnimationCounter - (zoomAnimationTime / 2)) / (zoomAnimationTime / 2)));
		if (zoomAnimationCounter >= zoomAnimationTime) {
			zoomAnimation = false;
		}
		else {
			worldZoom += zoomAnimationQuantity;
		}
	}

	worldZoom += realWorldZoom;

	if (vibrationCounter > 0) {
		vibrationCounter -= Kang::gameTimeSpeed;
		vibration = Vector2(-vibrationForce + rand() % (int)(vibrationForce*2), -vibrationForce + rand() % (int)(vibrationForce * 2));
	}

	if (decreasingVibration) {
		vibration = Vector2(-vibrationForce + rand() % (int)(vibrationForce * 2), -vibrationForce + rand() % (int)(vibrationForce * 2));
		vibrationForce *= decreasingVibrationFactor;
		if (vibrationForce <= 1)
			decreasingVibration = false;
	}

	transform.position += vibration;


	
}

void Cam::StartSimpleVibration(float time, float force) {
	vibrationCounter = time;
	vibrationForce = force;
}

void Cam::StartDecreasingVibration(float d, float force) {
	decreasingVibration = true;
	decreasingVibrationFactor = d;
	vibrationForce = force;
}

void Cam::StopVibration() {
	vibrationCounter = 0;
	vibrationForce = 0;
	decreasingVibration = false;
}

void Cam::Draw() {

}

void Cam::StartSimpleZoomAnimation(float target, float time) {
	zoomAnimationCounter = 0;
	zoomAnimationTime = time;
	zoomAnimationTarget = target;
	zoomAnimation = true;
}

void Cam::StopZoomAnimation() {
	zoomAnimation = false;
}

void Cam::Clamp() {
	if (cameraBounds) {
		if (realWorldZoom >= 1) {
			float w = (SDLClass::screenSizeX / 2) / zoom;
			float h = (SDLClass::screenSizeY / 2) / zoom;
			transform.position.x = Meth::Clamp(transform.position.x, cameraBounds->rect.p1.x + w, cameraBounds->rect.p2.x - w);
			transform.position.y = Meth::Clamp(transform.position.y, cameraBounds->rect.p1.y + h, cameraBounds->rect.p2.y - h);
		}
	}
}

