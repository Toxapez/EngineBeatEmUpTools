#pragma once
#include "Text.h"
#include "OpenGLClass.h"

class TextDrawer
{
public:
	enum Alineo { ALIN_LEFT, ALIN_CENTERED, ALIN_RIGHT };
	enum Altura { ALT_UP, ALT_CENTERED, ALT_DOWN };
	
	static void Start();
	static void DrawSimpleText(Text text, Vector2 pos);
	static void DrawSimpleText(Text text, Vector2 pos, Alineo alin);
	static void DrawSimpleText(Text text, Vector2 pos, Altura alt);
	static void DrawSimpleText(Text text, Vector2 pos, Alineo alin, Altura alt);
	
	static Mesh rectM;
	static RectP rect;
};
