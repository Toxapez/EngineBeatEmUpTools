#include "Text.h"
TTF_Font* Text::usedFont = nullptr;
std::string Text::currentFont;
int Text::currentSize = 0;



Text::Text(string _text, int _size, Color _color, string _font, bool cd) {
	text = _text;
	size = _size;
	color = _color;
	font = _font;
	camDependent = cd;
}


Text::Text(string _text) {
	text = _text;
	size = 12;
	color = Color();
	font = "arial";
}

Text::Text() {
	text = "";
	size = 10;
	color = Color();
	font = "arial";
}



Vector2 Text::GetSize() {
	ChangeFont(*this);
	SDL_Rect Message_rect;
	TTF_SizeText(usedFont, text.c_str(), &Message_rect.w, &Message_rect.h);
	return Vector2(Message_rect.w, Message_rect.h);
}

void Text::ChangeFont(Text text) {
	int size = text.size * (text.camDependent ? Cam::currentCam->zoom : SDLClass::screenWidthStreching);
	if (currentFont != text.font || size != currentSize) {
		TTF_CloseFont(usedFont);
		usedFont = TTF_OpenFont(string("assets/fonts/" + text.font + ".ttf").c_str(), size);
		currentFont = text.font;
		currentSize = size;
	}
}