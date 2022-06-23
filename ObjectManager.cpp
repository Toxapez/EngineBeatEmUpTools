#include "ObjectManager.h"

bool compFirst(GameObject* a, GameObject* b) { return a->transform.position.y < b->transform.position.y; }

void ObjectManager::Update() {
	//gotta move this shit
	if (Keyboard::KeyboardCheck(SDL_SCANCODE_Z)) {
		Cam::currentCam->worldZoom += .01;
		//Cam::currentCam->rotation += .05;
		//SDLClass::ChangeWindowSize(SDLClass::screenSizeX * .9, SDLClass::screenSizeY * .9);
	}
	if (Keyboard::KeyboardCheck(SDL_SCANCODE_X)) {
		if (Cam::currentCam->worldZoom > .05) {
			Cam::currentCam->worldZoom -= .01;
			//Cam::currentCam->rotation -= .05;
		}
		//SDLClass::ChangeWindowSize(SDLClass::screenSizeX * 1.1, SDLClass::screenSizeY * 1.1);
	}
	if (Keyboard::KeyboardCheck(SDL_SCANCODE_C)) {
		Cam::currentCam->worldZoom = 1;
		//Cam::currentCam->rotation = 0;
	}
	//if (Keyboard::KeyboardCheck(SDL_SCANCODE_F))
		//SDLClass::FullScreen();
	if (Cam::currentCam) {
		Vector2 centerCam = Cam::currentCam->transform.position;
		BoxCollider b = BoxCollider((centerCam- Vector2(SDLClass::screenSizeX, SDLClass::screenSizeY)/.5)-Vector2(80,80), (centerCam+ Vector2(SDLClass::screenSizeX, SDLClass::screenSizeY)/.5));
		for (int i = 0; i < GameObject::gameObjects.placerScope; i++) {
			GameObject* c = GameObject::gameObjects[i];
			if (c->exists) {
				if (c->resistant) {
					//c->isActive = ColliderManager::CollidingBoxPoint(&b, c->transform.position);
				}
				else {
					if (c->isActive) {
						//if (!ColliderManager::CollidingBoxPoint(&b, c->transform.position)) {
						//	//c->isActive = false;
						//}
					}
				}
				
			}
		}
	}

	std::list<GameObject*> layers[] = { GameObject::downLayerList ,GameObject::dinamicLayerList, GameObject::upperLayerList };
	GameObject::ArrangeLayers();
	GameObject::dinamicLayerList.sort(compFirst);


	for (int i = 2; i > -1; i--)
	{
		auto it = layers[i].end();
		while (it != layers[i].begin()) {
			it--;
			auto c = *it;
			if (c->isActive) {
				bool happen = true;
				if (LevelEditor::instance.editting) {
					if (c->placeableObject) {
						happen = false;
						PlaceableObject* p = (PlaceableObject*)c;
						p->EditorUpdate();
					}
				}
				if (happen) {
					c->Update();
				}

			}
		}

	}
	Cam::currentCam->Clamp();
}


void ObjectManager::Draw() {
	Vector2 offSetCam;
	Vector2 offSetWindow;
	
	Cam::currentCam->zoom = Cam::currentCam->worldZoom * SDLClass::screenWidthStreching;
	//rrrrrrr
	if (Cam::currentCam) {
		offSetCam = Cam::currentCam->transform.position - ((Vector2(SDLClass::screenSizeX, SDLClass::screenSizeY) / 2) /Cam::currentCam->zoom) ;
		offSetWindow = ((Vector2(SDLClass::screenSizeX, SDLClass::screenSizeY) / 2) / Cam::currentCam->zoom) * -1;
	}
	std::list<GameObject*> layers[] = { GameObject::downLayerList ,GameObject::dinamicLayerList, GameObject::upperLayerList };
	GameObject::ArrangeLayers();
	GameObject::dinamicLayerList.sort(compFirst);
	for (int i = 0; i < GameObject::gameObjects.placerScope; i++) {
		GameObject* c = GameObject::gameObjects[i];
		if (c->isActive) {
			c->transform.UpdateOriginalPos();
			if (c->camDependent) {
				c->transform.position -= offSetCam;
				c->transform.position *= Cam::currentCam->zoom;
			}
			else {
				c->transform.position -= offSetWindow;
				c->transform.position *= SDLClass::screenWidthStreching;;
			}
		}
	}
	
	for (int i = 0; i < GameObject::gameObjects.placerScope; i++) {
		GameObject* c = GameObject::gameObjects[i];
			if (c->isActive && c->camDependent) {
				c->transform.position = c->transform.position.RotateRef(Cam::currentCam->rotation, Vector2(SDLClass::screenSizeX, SDLClass::screenSizeY) / 2);
			}
	}


	
	for (int i = 0; i < 3; i++)
	{
		for (auto c : layers[i]) { 
			if (c->isActive) {
				c->Draw();
				if (LevelEditor::instance.editting) {
					if (c->placeableObject) {
						PlaceableObject* p = (PlaceableObject*)c;
						p->EditorDraw();
					}
				}
			}
		}
	}
	Collider::AllUpdate();
	Collider::AllDraw();
	for (int i = 0; i < 3; i++)
	{
		for (auto c : layers[i]) {
			if (c->isActive) {
				c->transform.RestoreOriginalPos();
			}
		}
	}
}