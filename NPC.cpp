#include "NPC.h"
Scoper50<NPC> NPC::placerScope;
std::map<std::string, SpriteStatic> NPC::sprites;

NPC::NPC() {
	name = "";
	firstTimeDialog = "";
	repeatDialog = "";
	hasSettings = true;
	isActive = false;
	hasSpeak = false;
	layer = 0;
}

void NPC::AfterStaticStart() {
	if (sprites.empty()) {
		
		for (auto& p : std::filesystem::directory_iterator("assets/sprites/npc")) {
			std::string dir = p.path().string();
			int k = dir.size();
			k -= 5;
			std::string n;
			while (dir[k] != '\\') {
				k--;
			}
			k++;
			while (dir[k] != '.') {
				n.push_back(dir[k]);
				k++;
			}

			sprites.insert(std::pair<std::string, SpriteStatic>(n, SpriteStatic()));
			sprites.at(n).Set("npc/" + n + ".png");
			
		}
	}
}

void NPC::Update() {
	if (firstTimeDialog != "" && !DialogUI::instance.inDialog && !hasSpeak) {
		float distance = (Player::player.transform.position - transform.position).Magnitude();
		playernear = distance < 180;
		if (playernear) {
			if (InputManager::attack) {
				DialogUI::instance.StartDialog(firstTimeDialog);
				hasSpeak = true;
			}
		}
	}

	if (name + customConfig == "empleado1") {
		if (!DialogUI::instance.inDialog && hasSpeak) {
			isActive = false;
			exists = false;
			LevelState::instance.wavesActive = true;
			Audio::instance.music.Play("bgmusic/banco1", true);
		}
	}else if (name + customConfig == "empleado2") {
		if (!DialogUI::instance.inDialog && hasSpeak) {
			isActive = false;
			exists = false;
		}
	}
}
void NPC::Draw() {
	if (currentSprite)
		currentSprite->Draw(transform.position);
	if (firstTimeDialog != "" && !DialogUI::instance.inDialog && !hasSpeak) {
		exclamationSpr->Draw(transform.position);
		if (playernear) {
			indicationSpr->Draw(Player::player.transform.position);
		}
	}
}

PlaceableObject* NPC::Set(Vector2 pos, int ID) {
	playernear = false;
	transform.position = pos;
	isActive = true;
	hasSpeak = false;
	if(name != "")
		currentSprite = &sprites.at(name);
	exclamationSpr = &sprites.at("alertanpc");
	exclamationSpr->offset = Vector2(0, -100);
	indicationSpr =  &sprites.at("spaceIndication");
	indicationSpr->offset = Vector2(0, -150);
	return this;
}



void NPC::SetSettings() {
	EmergentMessage::ForceEmergentMessage("Colocando NPC Configure en la consola.\n");
	std::string s;
	Console::SendLineMessage("Introduzca el nombre del NPC, este sera usado para definir su sprite");
	std::cin >> s;
	name = s.c_str();
	Console::SendLineMessage("Introduzca el nombre del primer dialogo si tiene, si no introduzca NO");
	std::cin >> s;
	if (s.c_str() != "NO")
		firstTimeDialog = s.c_str();
	Console::SendLineMessage("Introduzca el nombre del dialogo de repeticion si tiene, si no introduzca NO");
	std::cin >> s;
	if (s.c_str() != "NO")
		repeatDialog = s.c_str();
	Console::SendLineMessage("Introduzca el numero del configuracionCustom, si no tiene introduzca 0");
	std::cin >> s;
	customConfig = s.c_str();
	currentSprite = &sprites.at(name);
}