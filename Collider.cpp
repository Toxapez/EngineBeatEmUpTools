#include "Collider.h"
Scoper100000<Collider*> Collider::colliders;

Collider::Collider() {
	isActive = nullptr;
	type = 0;
	drawable = false;
	refPos = nullptr;
	gameObject = nullptr;
	layer = -1;
}
//-2 proyectiles regresados
//0 block
//1 objectsPateables
//3 enemies
//4 proyectiles pegables
//5 pushcolliders

void Collider::AllUpdate() {
	for (int i = 0; i < Collider::colliders.placerScope; i++) {
		
		Collider* c = Collider::colliders[i];
		if (c->isActive) {
			
			if (*c->isActive) {
				c->Update();
			}
		}
	}
}

void Collider::AllDraw() {
	for (int i = 0; i < Collider::colliders.placerScope; i++) {
		Collider* c = Collider::colliders[i];
		if (c->isActive) {
			if (*c->isActive) {
				c->Draw();
			}
		}
	}
}