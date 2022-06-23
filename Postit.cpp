#include "Postit.h"
Scoper100<Postit> Postit::placerScope;

Postit::Postit() {
	collider.Set(Vector2(),Vector2(LEVELTILESIZE, LEVELTILESIZE),this);
	hasSettings = true;
	textbox = TextBox(Vector2(5, 2), Rect(Vector2(), Vector2(LEVELTILESIZE * 2, LEVELTILESIZE * 2)), Color(0), Color(255,255,0));
}

PlaceableObject* Postit::Set(Vector2 pos, int ID) {
	transform.position = pos;
	textbox.refPos = &transform.position;
	textbox.displayText.size = 20;
	textbox.displayText.text = message;
	textbox.displayText.color = Color(0);
	isActive = true;
	exists = true;
	return this;
}

void Postit::SetSettings() {
	EmergentMessage::ForceEmergentMessage("Colocando Post-It Configure en la consola.\n");
	Console::SendLineMessage("Introduzca el mensaje que colocara en el post-IT");
	std::getline(std::cin, message);
	textbox.displayText.text = message;
}

void Postit::EditorUpdate() {
	Vector2 mp = Mouse::GetVector2PosRef(Cam::currentCam);
	touched = ColliderManager::CollidingBoxPoint(&collider, mp);
}

void Postit::EditorDraw() {
	
	if (touched)
		textbox.Draw();
	else
		FigureDrawer::DrawFillRectRef(Rect(Vector2(LEVELTILESIZE, LEVELTILESIZE)),Color(255,255,0),transform);
}