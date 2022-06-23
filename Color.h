#pragma once
#include "SDL.h"
struct Color
{
	int r;
	int g;
	int b;
	int a;
	Color();
	Color(int r, int g, int b, int a);
	Color(int r, int g, int b);
	Color(int b);
	SDL_Color ToSDL();
	bool operator==(Color other);
};



