#include "VectorFigureDrawer.h"
SDL_Surface* VectorFigureDrawer::circleTexture = nullptr;
SDL_Surface* VectorFigureDrawer::flanTexture = nullptr;

void VectorFigureDrawer::Start() {
	circleTexture = TextureLoader::LoadTexture("sprites/Circle.png");
	flanTexture = TextureLoader::LoadTexture("sprites/WhiteFlan30x30.png");
}

void VectorFigureDrawer::DrawCircle(Circle circle, Color c) {
	//SDL_SetTextureColorMod(circleTexture, c.r, c.g, c.b);
	//SDL_SetTextureAlphaMod(circleTexture, c.a);
	SDL_Rect r = circle.ToRect().ToSDLRect();
	//SDL_RenderCopy(SDLClass::renderer, circleTexture, NULL, &r);
}

void VectorFigureDrawer::DrawRectCircle(Rect r, Color c) {
	SDL_Rect rect = r.ToSDLRect();
}

void VectorFigureDrawer::DrawRectFlan(Rect r, Color c) {
	SDL_Rect rect = r.ToSDLRect();
}