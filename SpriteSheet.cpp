#include "SpriteSheet.h"
SpriteSheet::SpriteSheet() {

}

void SpriteSheet::Set(Vector2 ss, int ns, int w) {
	slotSize = ss;
	nSlots = ns;
	width = w;

	setlocale(LC_ALL, "");
	std::string path = std::string("assets/info/recolectables/leshes.tsv");
	std::ifstream input_file(path);
	std::string fullfile = std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
	int k = 0;
	for (int i = 0; i < nSlots; i++)
	{
		std::string t;
		std::string d;
		while (fullfile[k] != '\t')
		{
			t.push_back(fullfile[k]);
			k++;
		}
		k++;
		while (fullfile[k] != '\n')
		{
			d.push_back(fullfile[k]);
			k++;
			if (!(k < fullfile.size())) {
				break;
			}
		}
		k++;
		infos.push_back(std::pair(t,d));
	}
}

void SpriteSheet::Draw(int n, Vector2 pos, bool camDependent, bool facingside, float rot, SDL_Rect r, float scale, Vector2 vScale) {

	if (baseSprite.it) {
		Vector2 spriteSize = slotSize * (camDependent ? Cam::currentCam->zoom : SDLClass::screenWidthStreching) * scale;
		spriteSize = Vector2(spriteSize.x * vScale.x, spriteSize.y * vScale.y);
		RectTwoPoint spriteRect = RectTwoPoint(spriteSize * -.5, spriteSize);
		if (r.w == 0) {
			Vector2 finalOffset = Cam::currentCam->rotation == 0 ? baseSprite.offset : baseSprite.offset.Rotate(Cam::currentCam->rotation);
			r = ((Rect(spriteRect.p1, spriteRect.p2) + pos + finalOffset * Cam::currentCam->zoom)).ToSDLRect();
		}
		SDL_Point p = { r.w / 2, r.h / 2 };
		SDL_Rect cutR = Rect(Vector2( n % width * slotSize.x, n / width * slotSize.y), slotSize).ToSDLRect();
		//SDL_RenderCopyEx(SDLClass::renderer, baseSprite.it, &cutR, &r, Meth::RadToDeg(rot + (camDependent ? Cam::currentCam->rotation : 0)), &p, facingside ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
	}
}