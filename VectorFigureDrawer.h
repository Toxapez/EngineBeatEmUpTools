#pragma once
#include "TextureLoader.h"
#include "Circle.h"
class VectorFigureDrawer
{
	static SDL_Surface* circleTexture;
	static SDL_Surface* flanTexture;
public:
	static void Start();
	static void DrawCircle(Circle , Color c);
	static void DrawRectCircle(Rect , Color c);
	static void DrawRectFlan(Rect, Color c);
};

