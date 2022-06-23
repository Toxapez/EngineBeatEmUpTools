#include "SpriteStatic.h"

std::vector<SpriteStatic*> SpriteStatic::sprites;

SpriteStatic::SpriteStatic() {
	
}
SpriteStatic* SpriteStatic::Set(std::string _name, Vector2 _size ,Vector2 os) {
	if (dir == "") {
		dir = _name;
		offset = os;
		size = _size;
		spriteRect = RectTwoPoint(size * -.5, size);
		camDependent = true;
		sprites.push_back(this);
	}
	return this;
}

SpriteStatic* SpriteStatic::ForcedSet(std::string _name, Vector2 _size, Vector2 os) {
	dir = _name;
	offset = os;
	size = _size;
	spriteRect = RectTwoPoint(size * -.5, size);
	camDependent = true;
	return this;
}

void SpriteStatic::Start() {
	for (auto c : sprites) {
		if (c) {
			c->Load();
		}
	}
}

void SpriteStatic::Load() {
	auto surface  = TextureLoader::LoadTexture("sprites/" + dir);

	
	OpenGLClass::LoadTextureFromSurface(surface, &it);
	if (size == Vector2(-1, -1)) {
		SDL_Point s;
		size = Vector2(surface->w, surface->h);
		spriteRect = RectTwoPoint(size * -.5, size);
	}

	SDL_FreeSurface(surface);
}

void SpriteStatic::ExternalLoad() {
	auto surface = IMG_Load((dir).c_str());

	OpenGLClass::LoadTextureFromSurface(surface, &it);
	if (size == Vector2(-1, -1)) {
		SDL_Point s;
		size = Vector2(surface->w, surface->h);
		spriteRect = RectTwoPoint(size * -.5, size);
	}

	SDL_FreeSurface(surface);
}

void SpriteStatic::Clear() {
	glDeleteTextures(1,&it);
	it = 0;
}

void SpriteStatic::Draw(Vector2 pos, bool facingside, float rot, SDL_Rect r, float scale, Vector2 vScale, Color c) {
	if (it) {
		Vector2 spriteSize = size * (camDependent? Cam::currentCam->zoom : SDLClass::screenWidthStreching) * scale;
		spriteSize = Vector2(spriteSize.x * vScale.x, spriteSize.y *vScale.y);
		spriteRect = RectTwoPoint(spriteSize * -.5, spriteSize);
		if (r.w == 0) {
			Vector2 finalOffset = Cam::currentCam->rotation == 0 ? offset : offset.Rotate(Cam::currentCam->rotation);
			r = ((Rect(spriteRect.p1, spriteRect.p2) + pos + finalOffset *Cam::currentCam->zoom)).ToSDLRect();
		}
		Vector2 p = Vector2(r.w / 2, r.h / 2 );
		FigureDrawer::DrawTexture(it, r,c,!facingside,false,rot,p);
		//SDL_RenderCopyEx(SDLClass::renderer, it, NULL, &r, Meth::RadToDeg(rot + (camDependent ? Cam::currentCam->rotation : 0)) , &p, facingside ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
	}
}

Vector2 SpriteStatic::GetSize() {
	return Vector2(size.x, size.y) * SDLClass::screenWidthStreching;
}

SpriteStatic::~SpriteStatic() {
	//SDL_FreeSurface(it);
}

void SpriteStatic::LoadAllSpritesInFolder(std::map<std::string, SpriteStatic>* map, std::string folderdir) {
	for (auto& p : std::filesystem::directory_iterator("assets/sprites/" + folderdir)) {
		std::string dir = p.path().string();
		int k = dir.size();
		k -= 5;
		std::string name;
		while (dir[k] != '\\') {
			k--;
		}
		k++;
		while (dir[k] != '.') {
			name.push_back(dir[k]);
			k++;
		}

		map->insert(std::pair<std::string, SpriteStatic>(name, SpriteStatic()));
		map->at(name).Set(folderdir + "/" + name + ".png");
		map->at(name).camDependent = false;
	}
}