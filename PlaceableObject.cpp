#include "PlaceableObject.h"
PlaceableObject::PlaceableObject() {
	placeableObject = true;
	hasSettings = false;
	needSecondPos = false;
	isActive = false;
}

PlaceableObject* PlaceableObject::Set(Vector2 pos, int ID) {
	transform.position = pos;
	isActive = true;
	return this;
}


void PlaceableObject::SetSettings() {

}

void PlaceableObject::EditorDraw() {

}

void PlaceableObject::SetSecondPos(Vector2 pos) {

}

void PlaceableObject::DeactivateAllType(int ID) {
	DeactivateAll();
}