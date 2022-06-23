#include "ObjetosInteracbles.h"

std::map<std::string, SpriteStatic> ObjetosInteracbles::sprites;
Scoper500<ObjetosInteracbles> ObjetosInteracbles::placerScope;
std::vector<ObjetoInteracbleInitInfo> ObjetosInteracbles::ois;
int ObjetosInteracbles::offsetObjects;

ObjetosInteracbles::ObjetosInteracbles() {
	collider.Set(Vector2(), Vector2(), this);
	//collider.drawable = true;
	layer = 0;
	facingFlipSpeed = Meth::SegToFrame(.7);
	
}

void ObjetosInteracbles::Update() {
	if (collider.layer != 1) {
		transform.position += speed;
		if (name == "silla") {
			facingFlipCounter += Kang::gameTimeSpeed;
			if (facingFlipCounter > facingFlipSpeed) {
				facingFlipCounter -= facingFlipSpeed;
				facing = !facing;
			}

		}
		else {
			rotation += speed.Magnitude() / 150;
			if (rotation > Meth::PI * 2) {
				rotation -= Meth::PI * 2;
			}
		
		}
		bool broke = false;
		for (int i = 0; i < Collider::colliders.placerScope; i++) {
			auto c = Collider::colliders[i];
			if (*c->isActive) {
				if (c->layer == 0)
					if (ColliderManager::BoxBoxEdgesInside((BoxCollider*)c, &collider)) {
						transform.position -= speed;
						if (((BoxCollider*)c)->originalPoints.second.x > ((BoxCollider*)c)->originalPoints.second.y)
							speed.y *= -1;
						else speed.x *= -1;
						broke = true;

						if (LevelState::instance.nEnemies > 0) {
							Vector2 dirAngle = (speed).Normalize();
							float nearest = 2000;
							Vector2* nearestV = nullptr;
							for (auto c : Being::activeBeings) {
								if (c->gameObject->isActive) {
									if (*c->gameObject != *this) {
										Vector2 v = speed;
										float dist = v.Magnitude();
										if (dist < nearest) {
											if (((dirAngle * v.Magnitude()) - v).Magnitude() < 1200) {
												nearestV = &c->gameObject->transform.position;
												nearest = dist;
											}
										}
									}
								}
							}
							if (nearestV) {
								AutoAim(*nearestV);
							}
						}
					}
				if (c->layer == 3)
					if (ColliderManager::BoxBoxEdgesInside((BoxCollider*)c, &collider)) {
						dynamic_cast<Being*>(c->gameObject)->Damage(transform.position, fuerza);
						transform.position -= speed;
						speed = (transform.position - c->gameObject->transform.position).Normalize() * 35;
						broke = true;

						if (LevelState::instance.nEnemies > 0) {
							Vector2 dirAngle = (speed).Normalize();
							float nearest = 2000;
							Vector2* nearestV = nullptr;
							for (auto c : Being::activeBeings) {
								if (c->gameObject->isActive) {
									if (*c->gameObject != *this) {
										Vector2 v = speed;
										float dist = v.Magnitude();
										if (dist < nearest) {
											if (((dirAngle * v.Magnitude()) - v).Magnitude() < dist *.8) {
												nearestV = &c->gameObject->transform.position;
												nearest = dist;
											}
										}
									}
								}
							}
							if (nearestV) {
								AutoAim(*nearestV);
							}
						}
					}
				if (broke) {
					durability--;
					Particle::scoper.GetNextScope().Set("impacto1", transform.position);
					Audio::instance.sfx.Play("effect/hit");
					if (durability <= .1) {
						isActive = false;
						exists = false;
					}
					break;
				}
			}
		}
		if (impulso > 0) {
			impulso--;
			
		}
		if (impulso <= 0) {
			if (rotation <= .1) {
				rotation = 1;
				collider.layer = 1;
			}
		}
	}
	else {
		if (rotation > 0) {
			rotation -= Kang::gameTimeSpeed * 1;
			if (rotation <= 0) {
				rotation = 0;
				Audio::instance.sfx.Play("objetosInteracbles/objfall");
			}
		}
	}
	if (spawnSquashCounter > 0) {
		spawnSquashCounter -= Kang::gameTimeSpeed * .2;
	}

	
}

void ObjetosInteracbles::Throw(Vector2 otherPos, float f) {
	collider.layer = -1;
	fuerza = f;
	impulso = Meth::SegToFrame(f/3);
	speed = (transform.position - otherPos).Normalize() * 35;
	rotation = 0;
	Events::instance.throwObject.happened = true;
}

void ObjetosInteracbles::AutoAim(Vector2 pos) {
	speed = (pos - transform.position).Normalize() * 35;
}

void ObjetosInteracbles::Draw() {
	//squash spawn
	Vector2 spriteSize = Vector2(355, 200) * Cam::currentCam->zoom ;
	RectTwoPoint spriteRect = RectTwoPoint(spriteSize * -.5, spriteSize);
	SDL_Rect r;
	if (spawnSquashCounter > 1.5) {
		r = ((Rect(Vector2(spriteRect.p1.x * 1.2, spriteRect.p1.y * .3), Vector2(spriteRect.p2.x * 1.2, spriteRect.p2.y * .3)) + transform.position)).ToSDLRect();
	}
	else if (spawnSquashCounter > 0) {
		r = ((Rect(Vector2(spriteRect.p1.x * .5, spriteRect.p1.y * 1.5), Vector2(spriteRect.p2.x * .5, spriteRect.p2.y * 1.5)) + transform.position)).ToSDLRect();
	}
	else r = ((Rect(spriteRect.p1, spriteRect.p2) + transform.position)).ToSDLRect();
	currentSprite->Draw(transform.position, facing, rotation, r);

	collider.Update();
	//for (int i = 0; i < 4; i++)
	//{
	//	casters[i]->body = collider.lineas[i];
	//}
}

void  ObjetosInteracbles::AfterStaticStart() {
	for (int i = 0; i < 4; i++)
		casters.push_back(new ShadowCaster(Line(),nullptr));
}

void ObjetosInteracbles::ReadAllObjects() {
	std::string n, dCS1, dCS2, os1, os2, d;
	std::vector<std::string*> vars;

	vars.push_back(&n);
	vars.push_back(&dCS1);
	vars.push_back(&dCS2);
	vars.push_back(&os1);
	vars.push_back(&os2);
	vars.push_back(&d);

	Reader::SetReader("assets/info/interacbles/1.tsv", &vars);

	while (!Reader::IsFinished()) {
		Reader::Read();
		ois.push_back({ n, Vector2(std::stoi(dCS1),std::stoi(dCS2)), Vector2(std::stoi(os1),std::stoi(os2)) ,std::stoi(d) });
	}
	for (int i = 0; i < ois.size(); i++)
	{

		auto spr = sprites.insert(std::pair(ois[i].name, SpriteStatic()));

		(*spr.first).second.Set("objects/" + ois[i].name + ".png", Vector2(-1, -1), Vector2());
	}
}

PlaceableObject* ObjetosInteracbles::Set(Vector2 pos, int ID)  {
	transform.position = pos;
	isActive = true;
	SetType(ID);
	rotation = 0;
	facing = true;

	return this;
}

void ObjetosInteracbles::SetType(int ID) {
	collider.layer = 1;
	int id = ID - offsetObjects;
	Vector2 defaultCS = ois[id].defaultCS; 
	Vector2 offset = ois[id].offset;
	name = ois[id].name;
	collider.Set(defaultCS * -.5 + offset, defaultCS * .5 + offset, this);
	currentSprite = &sprites.at(name);
	durability = 3; 
	//for (int i = 0; i < 4; i++)
	//	casters[i]->gameobject = this;
}