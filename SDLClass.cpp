#include "SDLClass.h"
SDL_Window* SDLClass::window;
SDL_Renderer* SDLClass::renderer;
int SDLClass::screenSizeX = 1920;
int SDLClass::screenSizeY = 1080;
double SDLClass::screenWidthStreching = ((double)SDLClass::screenSizeX / 1920);
SDL_Texture* SDLClass::texture = nullptr;
SDL_Surface* SDLClass::surface = nullptr;
Color SDLClass::colorWindow;
bool SDLClass::close = false;
bool SDLClass::triangulate = false;

std::vector<std::vector<Vector2>> SDLClass::edgeRecords;


void SDLClass::CrearVentana() {

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();


	window = SDL_CreateWindow("ToxaEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenSizeX, screenSizeY, SDL_WINDOW_OPENGL);


	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	//ChangeWindowSize(200, 140);
	
}

void SDLClass::Finish() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void SDLClass::Start() {
	CrearVentana();
}

void SDLClass::Clear() {
	SDL_RenderClear(SDLClass::renderer);
}

void SDLClass::Present() {

	//SDL_SetRenderDrawColor(SDLClass::renderer, colorWindow.r, colorWindow.g, colorWindow.b, colorWindow.a);
	//SDL_RenderPresent(SDLClass::renderer);
	

}

void SDLClass::ChangeWindowSize(int w, int h) {
	SDL_DisplayMode DM;
	int m = SDL_GetWindowDisplayIndex(window);
	SDL_GetCurrentDisplayMode(m, &DM);
	if (w <= DM.w) {
		SDL_SetWindowSize(window, w, h);
		screenSizeX = w;
		screenSizeY = h;

		SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED_DISPLAY(m), SDL_WINDOWPOS_CENTERED_DISPLAY(m));
		SDLClass::screenWidthStreching = ((double)SDLClass::screenSizeX / 1920);
	}
}

void SDLClass::FullScreen() {
	SDL_DisplayMode DM;
	int m = SDL_GetWindowDisplayIndex(window);
	SDL_GetCurrentDisplayMode(m, &DM);
	ChangeWindowSize(DM.w, DM.h);
}

SDL_Texture* SDLClass::LoadTexture(std::string dir) {
	surface = IMG_Load(dir.c_str());

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	return texture;
}

void SDLClass::DrawTexture(SDL_Texture* it, Vector2 pos) {
	int w, h;
	SDL_QueryTexture(it, NULL, 0, &w, &h);
	Vector2 spriteSize = Vector2(w, h);
	RectTwoPoint spriteRectT = RectTwoPoint(spriteSize * -.5, spriteSize);
	SDL_Rect r = ((Rect(spriteRectT.p1, spriteRectT.p2) + pos)).ToSDLRect();
	SDL_Point p = { r.w / 2, r.h / 2 };
	SDL_RenderCopyEx(SDLClass::renderer, it, NULL, &r, 0, &p, SDL_FLIP_NONE);
}

Vector2 SDLClass::GetScreenSizeVector2() {
	return Vector2(screenSizeX,screenSizeY);
}

void SDLClass::DrawOval(Vector2 pos, Vector2 size)
{
	
	SDL_SetRenderDrawColor(SDLClass::renderer, 25, 25, 25, 255);

	int right = pos.x + size.x;
	int bottom = pos.y + size.y;
	int a = size.x / 2;
	int b = size.y / 2;
	Vector2 center = pos + size/2;
	for (int i = pos.x; i < right; i+= 2) {
		for (int j = pos.y; j < bottom; j+=4) {
			Vector2 acomodate = Vector2(i, j) - center;
			if (pow(acomodate.x/a,2) + pow(acomodate.y / b, 2) <= 1) {
				SDL_RenderDrawPoint(renderer, i, j);
				SDL_RenderDrawPoint(renderer, i+1, j);
				SDL_RenderDrawPoint(renderer, i, j+1);
				SDL_RenderDrawPoint(renderer, i+1, j+1);
			}
		}
	}

	
	
	
}

void SDLClass::ChangeDrawColor(Color color) {
	SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);
}

void SDLClass::ChangeWindowTitle(std::string n) {
	SDL_SetWindowTitle(window, n.c_str());
}

