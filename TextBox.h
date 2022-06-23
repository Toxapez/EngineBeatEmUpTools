#pragma once
#include "TextDrawer.h"
#include "FigureDrawer.h"
struct TextBox
{
	enum Alineo { ALIN_LEFT, ALIN_CENTERED, ALIN_RIGHT };
	enum Altura { ALT_UP, ALT_CENTERED, ALT_DOWN };
	Alineo alineo;
	Rect containerRect;
	Rect originalMarkRect;
	Rect markRect;
	Text displayText;
	Color rectColor;
	Color bgColor;
	Rect endLine;
	Vector2 pos;
	TextBox();
	TextBox( Vector2 offset, Rect rContainer, Color = Color(-1), Color bgc = Color (-1));
	TextBox(Text, Vector2 offset, Rect rContainer, Color = Color(-1), Color bgc = Color(-1));
	void fitTextLinesLeft(string text, Rect rText);
	void fitTextLinesCentered(string text, Rect rText);
	void Draw();
	void SetOffSetMark(Vector2 offset, Rect rContainer);
	void SetOffSetMark();
	Vector2 offsetMark;
	Vector2* refPos;
	bool camDependent = true;
};





