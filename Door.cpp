#include "Door.h"
Scoper10<Door> Door::placerScope;
SpriteStatic Door::editorSprite;
std::string Door::loadLevel = "";
int Door::loadLevelDoorN;

Door::Door() {
	hasSettings = true;
	isActive = false;
}

void Door::AfterStaticStart() {
	editorSprite.Set("editor/door.png",Vector2(100,100));
}

void Door::Update() {
	BoxCollider b = BoxCollider(editorSprite.spriteRect.p1 + transform.position, editorSprite.spriteRect.p2 + transform.position);
	if (ColliderManager::Colliding(&Player::player.bodyCollider, &b)) {
		if (entrable) {
			entrable = false;
			loadLevel = destinyLevelName;
			loadLevelDoorN = destinyDoorNumber;
		}
	}
	else {
		entrable = true;
	}
}

void Door::Draw() {
	editorSprite.Draw(transform.position);
}

void Door::EditorDraw() {
	

}

PlaceableObject* Door::Set(Vector2 pos, int ID) {
	transform.position = pos;
	isActive = true;
	doorNumber = 0;
	destinyLevelName = "";
	destinyDoorNumber = 0;
	return this;
}

void Door::SetSettings() {
	EmergentMessage::ForceEmergentMessage("Colocando Door Configure en la consola.\n");
	std::string s;
	Console::SendLineMessage("Introduzca el numero de puerta");
	std::cin >> s;
	doorNumber = atoi(s.c_str());
	Console::SendLineMessage("Introduzca el nombre del nivel de destino");
	std::cin >> s;
	destinyLevelName = s;
	Console::SendLineMessage("Introduzca el numero de puerta de destino");
	std::cin >> s;
	destinyDoorNumber = atoi(s.c_str());
}

PlaceableObject* Door::GetPlaceableObject(bool force) {
	if (!force) {
		if (AllUsed()) {
			DeactivateAll();
			return nullptr;
		}
	}
	return &placerScope.GetNextScope();
}

bool Door::AllUsed() {
	return placerScope.placerScope + 1 == placerScope.maxEntities;
}

void Door::DeactivateAll() {
	for (int i = 0; i < placerScope.maxEntities; i++) {
		placerScope[i].isActive = false;
		placerScope[i].exists = false;
	}
	placerScope.placerScope = 0;
}