#include "GameObject.h"

Scoper100000<GameObject*> GameObject::gameObjects;
std::list<GameObject*> GameObject::upperLayerList;
std::list<GameObject*> GameObject::dinamicLayerList;
std::list<GameObject*> GameObject::downLayerList;
int GameObject::idCounter = 0;

GameObject::GameObject() {
	gameObjects.GetNextScope() = this;
	isActive = true;
	placeableObject = false;
	resistant = true;
	exists = false;
	layer = 5;
	uniqueID = idCounter;
	idCounter++;
	camDependent = true;
}

void GameObject::Update() {

}

void GameObject::Draw() {

}

void GameObject::AfterStaticStart() {

}

void GameObject::AllAfterStaticStart() {
	for (int i = 0; i < gameObjects.placerScope; i++) {
		gameObjects[i]->AfterStaticStart();
	}
}


void GameObject::ArrangeLayers() {
	upperLayerList.clear();
	dinamicLayerList.clear();
    downLayerList.clear();
	for (int j = -15; j < 30; j++) {
		for (int i = 0; i < gameObjects.placerScope; i++) {
			GameObject* c = gameObjects[i];
			if (j < 0) {
				if (c->layer == j) {
					downLayerList.push_back(c);
				}
			}
			else if (j > 0) {
				if (c->layer == j) {
					upperLayerList.push_back(c);
				}
			}
			else if (j == 0) {
				if (c->layer == j) {
					dinamicLayerList.push_back(c);
				}
			} 
		}
	}
}

bool GameObject::operator==(GameObject other) {
	return uniqueID == other.uniqueID;
}
bool GameObject::operator!=(GameObject other) {
	return uniqueID != other.uniqueID;
}