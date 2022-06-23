#include "EditorMenu.h"

EditorMenu EditorMenu::instance;

EditorMenu::EditorMenu() {
	
	editorMCameraBounds = CameraBounds(RectTwoPoint(SDLClass::GetScreenSizeVector2() * -20, SDLClass::GetScreenSizeVector2() * 20));
	cam.SetCamMovible(transform.position,1,&editorMCameraBounds);
	cam.speed = 8;
	cam.transform.position.x += 200;
	ReadLevels();
	
}

void EditorMenu::AfterStaticStart() {
	ChangeGameState(this);
}

void EditorMenu::ReadLevels() {
	levels.clear();
	std::vector<std::string> names;
	for (auto& p : std::filesystem::directory_iterator("levels")) {
		if (p.path().filename().string().back() != 'g') {
			levels.push_back(std::pair(p.path().filename().string(), p));
			names.push_back(levels.back().first);
		}
	}
	levelOptions = OptionsBox(&transform.position, "Levels", Vector2(100, 30), names);
	std::vector<std::string> namesGeneralOption = {"New level"};
	generalOptions = OptionsBox(&transform.position,"Editor Menu", Vector2(120, 30), namesGeneralOption, Vector2(-110, 0));
}

void EditorMenu::Update() {
	if (PlayerVariables::instance.user) {
		ChangeGameState(gamestates[1]);
		LevelEditor::instance.LoadLevelFromFile(levels[0].first);
		Mouse::leftClickPressed = false;
	}
	int n = levelOptions.CollidingWithPoint(Mouse::GetVector2PosRef(Cam::currentCam));
	if (n > -1) {
		
		if (Mouse::leftClickPressed) {
			ChangeGameState(gamestates[1]);
			LevelEditor::instance.LoadLevelFromFile(levels[n].first);
			Mouse::leftClickPressed = false;
		}
	}
	n = generalOptions.CollidingWithPoint(Mouse::GetVector2PosRef(Cam::currentCam));
	if (n > -1) {
		if (Mouse::leftClickPressed) {
			if (n == 0) {
				ChangeGameState(gamestates[1]);
				std::string name;
				EmergentMessage::ForceEmergentMessage("Introduce nombre del nuevo nivel en la consola");
				std::cout << "Introduce nombre del nuevo nivel:\n";
				std::cin >> name;
				std::cout << "Nivel Creado regresa al programa.\n";
				LevelEditor::instance.NewLevel(name);
				Mouse::leftClickPressed = false;
			}
		}
	}

	if (Keyboard::KeyboardFirstPressed(SDL_SCANCODE_ESCAPE)){
		if(BooleanQuestion::AskQuestion("Desea salir del programa?"))
			SDLClass::close = true;
	}
		

}

void EditorMenu::Draw() {

	levelOptions.Draw();
	generalOptions.Draw();
}

void EditorMenu::SetActive(bool b) {
	Cam::currentCam = &cam;
	isActive = b;
	cam.transform.position = transform.position;
	cam.transform.position.x -= 500;
	if (b) {
		SDLClass::colorWindow = Color(25);
		ReadLevels();
	}
}