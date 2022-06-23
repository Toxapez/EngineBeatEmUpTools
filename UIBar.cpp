#include "UIBar.h"


void UIBar::AddPart(UIComponentGO* p) {
	parts.push_back(p);
}

void UIBar::UpdatePos(Vector2 os) {
	transform.position = os;
	UIBar::size = Vector2();
	float aditionalSize = 0;
	for (int i = 0; i < parts.size(); i++) {
		float offset = transform.position.x;
		parts[i]->transform.position.y = transform.position.y;
		aditionalSize += (i > 0 ? parts[i - 1]->size.x : 0);
		parts[i]->transform.position.x = offset + aditionalSize;
		UIBar::size.x += parts[i]->size.x;
		if (parts[i]->size.y > UIBar::size.y)
			UIBar::size.y = parts[i]->size.y;
	}
}



void UIBar::Update() {
	UpdatePos(transform.position);
}

void UIBar::SetActive(bool b) {
	for (int i = 0; i < parts.size(); i++) {
		parts[i]->SetActive(b);
	}
	UIComponentGO::SetActive(b);
}