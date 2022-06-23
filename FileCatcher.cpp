#include "FileCatcher.h"


FileCatcher::FileCatcher() {
	collider.Set(Vector2(), Vector2(), this);
	hasMadeChange = false;
	layer = 10;
}

void FileCatcher::Set(Vector2 p, Vector2 s) {
	transform.position = p;
	body = Rect(Vector2(),s);
	collider.Set(Vector2(), Vector2(body.w, body.h), this);
	tb = TextBox(Vector2(), body);
	//tb.alineo = TextBox::ALIN_CENTERED;
	message = Text("", 10, Color(0), "arial", false);
	size = Vector2(body.w, body.h);
}

void FileCatcher::Update() {
	bool hover = ColliderManager::CollidingBoxPoint(&collider, Mouse::GetVector2PosRef(Cam::currentCam));
	if (dir.empty()) {
		message.text = hover ? "Drop file to add" : "Drag file to add";
		message.color = hover ? Color(0,200,0) : Color(0, 0, 200);
		message.size = 20;
		if (hover) {
			if (Mouse::isFileDropped) {
				dir = Mouse::fileDroppedDir;
				hasMadeChange = true;
				deleteDelay = 30;
			}
		}
	}
	else {
		message.size = 15;
		message.text = "File Added: ..."  +StringUtilities::ClampString(dir,25,false) + " Click to erase.";
		if (hover)
			if(!deleteDelay)
				if (Mouse::leftClickPressed) {
					Clear();
				}
	}

	if (deleteDelay > 0)
		deleteDelay -= Kang::gameTimeSpeed;
}
void FileCatcher::Draw() {
	collider.Update();
	tb.pos = collider.GetCenter();
	FigureDrawer::DrawFillRectRef(body, Color(255), transform, false);
	FigureDrawer::DrawRectRef(body, Color(0), transform, false);
	tb.displayText = message;
	tb.Draw();
}

void FileCatcher::Clear() {
	dir.clear();
	hasMadeChange = true;
}