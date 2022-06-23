#include "WindowUIComponent.h"
void WindowUIComponent::UpdatePos(Vector2 os) {
	transform.position = os;
	size = Vector2();
	float aditionalSize = 0;
	for (int i = 0; i < parts.size(); i++) {
		float offset = transform.position.y;
		parts[i]->transform.position.x = transform.position.x;
		aditionalSize += (i > 0 ? parts[i - 1]->size.y : 0);
		parts[i]->transform.position.y = offset + aditionalSize;
		size.y += parts[i]->size.y;
		if (parts[i]->size.x > size.x)
			size.x = parts[i]->size.x;
	}
}
void WindowUIComponent::AddPart(UIComponentGO* p) {
	parts.push_back(p);
}

void WindowUIComponent::LastUpdatePos(Vector2 p) {
	for (int i = 0; i < parts.size(); i++) {
		parts[i]->transform.position += p;
	}
}

void WindowUIComponent::SetActive(bool b) {
	for (int i = 0; i < parts.size(); i++) {
		parts[i]->SetActive(b);
	}
	UIComponentGO::SetActive(b);
}