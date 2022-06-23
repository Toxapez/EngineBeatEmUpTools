#include "Tapiz.h"

std::vector<Color> Tapiz::colores;
std::vector<std::string> Tapiz::names;
Scoper10000<Tapiz> Tapiz::placerScope;
SpriteStatic Tapiz::defaultSpr;
float Tapiz::borderGross = 8;
Color Tapiz::borderColor = Color(0);

void Tapiz::Draw() {

	//SDL_SetTextureColorMod(defaultSpr.it, color->r, color->g, color->b);
	defaultSpr.size = Vector2(LEVELTILESIZE + (2/Cam::currentCam->zoom), LEVELTILESIZE  +(2 / Cam::currentCam->zoom));
	defaultSpr.offset = Vector2(LEVELTILESIZE, LEVELTILESIZE) / 2;
	defaultSpr.Draw(transform.position, true, 0, SDL_Rect(), 1, Vector2(1,1), *color);
	//FigureDrawer::DrawFillRectRef(Rect(LEVELTILESIZE/2 * Cam::currentCam->zoom, LEVELTILESIZE/2 * Cam::currentCam->zoom,LEVELTILESIZE, LEVELTILESIZE), *color, transform);
	//SDL_SetTextureColorMod(defaultSpr.it, borderColor.r, borderColor.g, borderColor.b);
	if (border[0]) {
		defaultSpr.size = Vector2(LEVELTILESIZE + (2 / Cam::currentCam->zoom), borderGross + (2 / Cam::currentCam->zoom));
		defaultSpr.offset = Vector2(LEVELTILESIZE , borderGross) / 2;
		defaultSpr.Draw(transform.position, true, 0, SDL_Rect(), 1, Vector2(1, 1), *color);
	}
	if (border[1]) {
		defaultSpr.size = Vector2(borderGross + (2 / Cam::currentCam->zoom), LEVELTILESIZE + (2 / Cam::currentCam->zoom));
		defaultSpr.offset = Vector2(borderGross, LEVELTILESIZE ) / 2;
		defaultSpr.Draw(transform.position, true, 0, SDL_Rect(), 1, Vector2(1, 1), *color);
	}
	if (border[2]) {
		defaultSpr.size = Vector2(borderGross + (2 / Cam::currentCam->zoom), LEVELTILESIZE + (2 / Cam::currentCam->zoom));
		defaultSpr.offset = Vector2(LEVELTILESIZE- borderGross/2, LEVELTILESIZE / 2);
		defaultSpr.Draw(transform.position, true, 0, SDL_Rect(), 1, Vector2(1, 1), *color);
	}
	if (border[3]) {
		defaultSpr.size = Vector2(LEVELTILESIZE + (2 / Cam::currentCam->zoom), borderGross + (2 / Cam::currentCam->zoom));
		defaultSpr.offset = Vector2(LEVELTILESIZE / 2, LEVELTILESIZE - borderGross/2 ) ;
		defaultSpr.Draw(transform.position, true, 0, SDL_Rect(), 1, Vector2(1, 1), *color);
	}

	defaultSpr.size = Vector2(borderGross + (2 / Cam::currentCam->zoom), borderGross + (2 / Cam::currentCam->zoom));
	if (corner[0]) {
		defaultSpr.offset = Vector2(borderGross, borderGross)/2;
		defaultSpr.Draw(transform.position, true, 0, SDL_Rect(), 1, Vector2(1, 1), *color);
	}
	if (corner[1]) {
		defaultSpr.offset = Vector2(LEVELTILESIZE - borderGross / 2, borderGross / 2);
		defaultSpr.Draw(transform.position, true, 0, SDL_Rect(), 1, Vector2(1, 1), *color);
	}
	if (corner[2]) {
		defaultSpr.offset = Vector2(borderGross / 2, LEVELTILESIZE - borderGross / 2);
		defaultSpr.Draw(transform.position, true, 0, SDL_Rect(), 1, Vector2(1, 1), *color);
	}
	if (corner[3]) {
		defaultSpr.offset = Vector2(LEVELTILESIZE - borderGross / 2, LEVELTILESIZE - borderGross / 2);
		defaultSpr.Draw(transform.position, true, 0, SDL_Rect(), 1, Vector2(1, 1), *color);
	}
}

void Tapiz::SetType(int ID) {
	color = &colores[ID];
}

void Tapiz::AfterStaticStart() {
	defaultSpr.Set("general/white_square.png", Vector2(0, 0), Vector2(LEVELTILESIZE, LEVELTILESIZE)/2);
}

void Tapiz::ReadAllColors() {
	std::string n, r, g, b;
	std::vector<std::string*> vars;

	vars.push_back(&n);
	vars.push_back(&r);
	vars.push_back(&g);
	vars.push_back(&b);

	Reader::SetReader("assets/info/tapiz/1.tsv", &vars);

	while (!Reader::IsFinished()) {
		Reader::Read();
		int n1 = std::stoi(r);
		int n2 = std::stoi(g);
		int n3 = std::stoi(b);
		colores.push_back(Color(n1,n2,n3));
		names.push_back(n);
	}
}