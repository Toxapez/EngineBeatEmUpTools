#include "EmergentMessage.h"

void EmergentMessage::ForceEmergentMessage(std::string message) {
	Vector2 size = Vector2(500, 80);
	Rect r2 = Rect(Vector2(10,10),size);
	Rect r1 = Rect(Vector2(SDLClass::GetScreenSizeVector2()/2 - size/2), size);
	TextBox textbox(Vector2(2,2), r1, Color(0));
	textbox.displayText.text = message;
	textbox.displayText.size = 30;
	textbox.alineo = TextBox::ALIN_CENTERED;
	OpenGLClass::Clear();
	textbox.Draw();
	OpenGLClass::Present();
}