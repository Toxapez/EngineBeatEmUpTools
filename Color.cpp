#include "Color.h"

Color::Color() {
	r = 255;
	g = 255;
	b = 255;
	a = 255;
}


Color::Color(int _r, int _g, int _b, int _a) {
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

Color::Color(int _r, int _g, int _b) {
	r = _r;
	g = _g;
	b = _b;
	a = 255;
}

Color::Color(int _b) {
	r = _b;
	g = _b;
	b = _b;
	a = 255;
}

SDL_Color Color::ToSDL() {
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return color;
}

bool Color::operator==(Color o) {
	return r == o.r && g == o.g && b == o.b;
}