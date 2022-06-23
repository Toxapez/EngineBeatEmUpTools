#include "BGItems.h"
std::vector<SpriteStatic*> BGItems::sprites;
Scoper1000<BGItems> BGItems::placerScope;
std::vector<std::string>  BGItems::names;

void BGItems::AfterStaticStart() {
}
void BGItems::ReadAllSprites() {
	std::string n, os1, os2;
	std::vector<std::string*> vars;

	vars.push_back(&n);
	vars.push_back(&os1);
	vars.push_back(&os2);

	Reader::SetReader("assets/info/bgitems/1.tsv", &vars);

	while (!Reader::IsFinished()) {
		Reader::Read();
		SpriteStatic* spr = new SpriteStatic();
		int n1 = std::stoi(os1);
		int n2 = std::stoi(os2);
		names.push_back(n);
		spr->Set("bg/" + n +".png", Vector2(-1, -1), Vector2(n1 != 0 ? LEVELTILESIZE / n1 : 0, n2 != 0 ? LEVELTILESIZE / n2 : 0));
		sprites.push_back(spr);
	}
}


BGItems::BGItems(){
	layer = -9;
}

void BGItems::Update() {
}

PlaceableObject* BGItems::Set(Vector2 pos, int ID) {
	transform.position = pos;
	isActive = true;
	SetSprite(ID);
	return this;
}

void BGItems::Draw() {
	currentSprite->Draw(transform.position);
}

void BGItems::EditorDraw() {
}


void BGItems::SetSprite(int ID) {
	currentSprite = sprites[ID];
}


PlaceableObject* BGItems::GetPlaceableObject(bool force) {
	if (!force) {
		if (AllUsed()) {
			DeactivateAll();
			return nullptr;
		}
	}
	return &placerScope.GetNextScope();
}

bool BGItems::AllUsed() {
	return placerScope.placerScope + 1 == placerScope.maxEntities;
}

void BGItems::DeactivateAll() {
	for (int i = 0; i < placerScope.maxEntities; i++) {
		placerScope[i].isActive = false;
		placerScope[i].exists = false;
	}
	placerScope.placerScope = 0;
}

bool BGItems::CreateNew(std::string n, std::string dir, Vector2 os) {
	FileUtilities::CopyAFile(dir.c_str(), "assets/sprites/bg", (n + ".png").c_str());
	SpriteStatic* spr = new SpriteStatic();
	int n1 = os.x;
	int n2 = os.y;
	names.push_back(n);
	spr->ForcedSet("bg/" + n + ".png", Vector2(-1, -1), Vector2(n1 , n2) * (LEVELTILESIZE/200));
	sprites.push_back(spr);
	spr->Load();
	return true;
}