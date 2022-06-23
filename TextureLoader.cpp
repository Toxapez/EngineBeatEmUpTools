#include "TextureLoader.h"



SDL_Surface* TextureLoader::LoadTexture(std::string c) {
	SDL_Surface* surface = IMG_Load(("assets/" + c).c_str());
	return surface;
}