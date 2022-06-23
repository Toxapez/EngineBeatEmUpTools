#include "OptionsBox.h"

OptionsBox::OptionsBox(Vector2* refPos, std::string name, Vector2 size, 
	std::vector<std::string> names, Vector2 originPos ) 
	: refPos(refPos), optionsCellSize(size), originPos(originPos) {
	optionsCellSize = size;
	title = TextBox(Vector2(5, 2), Rect(originPos, optionsCellSize), Color(0), Color(50));
	title.displayText.text = name;
	title.displayText.size = 20;
	title.refPos = refPos;
	for (int i = 0; i < names.size(); i++) {
		TextBox a(Vector2(5, 2), Rect(Vector2(originPos + Vector2(0, optionsCellSize.y * (i + 1))), optionsCellSize), Color(0), Color(50));
		a.displayText = names[i];
		a.refPos = refPos;
		options.push_back(a);
	}
	baseButtonColor = Color(0);
}

void OptionsBox::Draw() {
	title.containerRect.Pos(*refPos + originPos);
	title.originalMarkRect = Rect(originPos * Cam::currentCam->zoom, optionsCellSize );
	title.Draw();

	
	for (int i = 0; i < options.size(); i++) {
		options[i].containerRect.Pos(*refPos + originPos);
		options[i].originalMarkRect = Rect(Vector2(originPos + Vector2(0, optionsCellSize.y * (i + 1))) * Cam::currentCam->zoom, optionsCellSize );
		options[i].Draw();
	}
}

int OptionsBox::CollidingWithPoint(Vector2 p) {
	for (int i = 0; i < options.size(); i++) 
		options[i].rectColor = Color(baseButtonColor.r);
	for (int i = 0; i < options.size(); i++) {
		Rect colliderRect = Rect(Vector2(originPos + Vector2(0, optionsCellSize.y * (i + 1))), optionsCellSize);
		colliderRect.x += -colliderRect.w/2 + refPos->x;
		colliderRect.y += -colliderRect.h/2 + refPos->y;
		BoxCollider collider(Vector2(colliderRect.x, colliderRect.y), Vector2(colliderRect.x, colliderRect.y) + Vector2(colliderRect.w,colliderRect.h));
		collider.Update();
		if (ColliderManager::CollidingBoxPoint(&collider, p)) {
			options[i].rectColor = Color(baseButtonColor.r+100);
			return i;
		}
	}
	return -1;
}