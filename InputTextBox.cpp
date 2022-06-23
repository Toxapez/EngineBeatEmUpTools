#include "InputTextBox.h"

InputTextBox::InputTextBox() {
	hasMadeChange = false;
	collider.Set(Vector2(), Vector2(), this);
	layer = 10;
}

void InputTextBox::Set(Vector2 p, Rect b) {
	transform.position = p;
	body = b;
	collider.Set(Vector2(), Vector2(body.w, body.h), this);
	tb = TextBox(Vector2(),body);
	size = Vector2(body.w,body.h);
}

void InputTextBox::Update() {
	if (Mouse::leftClickPressed) {
		bool hover = ColliderManager::CollidingBoxPoint(&collider, Mouse::GetVector2PosRef(Cam::currentCam));
		if (hover) {
		}
		
		selected = hover;
		outLineColor = selected ? Color(0, 0, 255) : Color(55);
		color = selected ? Color(230, 230, 255) : Color(255);
		if (selected) {
			Keyboard::normalInputActive = false;
		}
		else {
			hasMadeChange = true;
			
			Keyboard::normalInputActive = true;
		}
	}
	if (selected) {
		if (Keyboard::textInputed)
			text.append(Keyboard::GetInputText());
		Keyboard::normalInputActive = true;
		if (Keyboard::KeyboardPressed(SDL_SCANCODE_BACKSPACE))
			if(!text.empty())
				text.pop_back();
		if (Keyboard::KeyboardPressed(SDL_SCANCODE_RETURN)) {
			hasMadeChange = true;
			selected = false;
		}
		Keyboard::normalInputActive = false;
	}
}
void InputTextBox::Draw() {
	collider.Update();
	tb.pos = collider.GetCenter();
	FigureDrawer::DrawFillRect(body + transform.position, color, false);
	FigureDrawer::DrawRect(body + transform.position, outLineColor, false);
	//TextDrawer::DrawSimpleText(, transform.position, TextDrawer::ALIN_LEFT, TextDrawer::ALT_UP);
	tb.displayText = Text(text, 15, Color(0), "arial", false);
	tb.Draw();
}

void InputTextBox::UpdateText(std::string t) {
	text = t;
	hasMadeChange = false;
}

void InputTextBox::Clear() {
	text.clear();
	selected = false;
	outLineColor = selected ? Color(0, 0, 255) : Color(55);
	color = selected ? Color(230, 230, 255) : Color(255);
}