#include "WindowUI.h"
WindowUI::WindowUI() {
	layer = 9;
	frameOffSet = Vector2(20,20);
	frameColor = Color(0,0,55);
	bodyColor = Color(0,0,155);
	collider.Set(Vector2(), Vector2(), this);
}

void WindowUI::Update() { 
	size = Vector2();
	for (int i = 0; i < components.size(); i++) {
		float aditionalSize = (i > 0 ? components[i - 1]->size.y : 0);
		components[i]->UpdatePos(Vector2(transform.position.x, transform.position.y + aditionalSize));
		size.y += components[i]->size.y;
		if (components[i]->size.x > size.x)
			size.x = components[i]->size.x;
	}

	for (int i = 0; i < components.size(); i++) 
		components[i]->LastUpdatePos(size/-2);

	collider.Set((size + frameOffSet) * -.5, (size + frameOffSet) * .5, this);
	collider.Update();
	if (Mouse::leftClickPressed) {
		bool hover = ColliderManager::CollidingBoxPoint(&collider, Mouse::GetVector2PosRef(Cam::currentCam));
		if (hover) {
			Mouse::leftClickPressed = false;
		}
	}
}
void WindowUI::Draw() {
	FigureDrawer::DrawFillRect(Rect(transform.position , size + frameOffSet ), frameColor);
	FigureDrawer::DrawFillRect(Rect(transform.position, size), bodyColor);
}


void WindowUI::AddComponent(WindowUIComponent* c) {
	components.push_back(c);
}

void WindowUI::SetActive(bool b) {
	for (int i = 0; i < components.size(); i++)
		components[i]->SetActive(b);
	isActive = b;
}