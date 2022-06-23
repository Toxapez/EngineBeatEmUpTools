#include "Loop.h"
void Loop::Start() {
	SDLClass::Start();
	OpenGLClass::Start();
	Mouse::Start();
	GameSystems::Start();
	GameObject::AllAfterStaticStart();//set all load dir here
	Animation::Start();
	SpriteStatic::Start();
	FigureDrawer::Start();
	TextDrawer::Start();
	InputManager::Start();
}
void Loop::FirstUpdate() {
	FrameController::FirstUpdate();
	GlobalStaticVariables::FirstUpdate();
	SDLClass::Clear();
	OpenGLClass::Clear();
	Mouse::Update();
	InputManager::Update();
	Collider::AllUpdate();
}
void Loop::Update() {
	ObjectManager::Update();
}
void Loop::LateUpdate() {
	ObjectManager::Draw();
	Keyboard::LateUpdate();
	Mouse::LateUpdate();
	SDLClass::Present();
	OpenGLClass::Present();
	FrameController::LateUpdate();
}
void Loop::Finish() {
	SDLClass::Finish();
}

bool Loop::Looping() {
	FirstUpdate();
	Update();
	LateUpdate();
	return !SDLClass::close;
}