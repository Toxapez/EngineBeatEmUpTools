#include "TextDrawer.h"

Mesh TextDrawer::rectM;
RectP TextDrawer::rect;

void TextDrawer::Start() {
	rectM = Mesh(&rect,
		glm::vec3(0, 0, 0),//pos
		glm::vec3(0),//origin
		glm::vec3(0),//rot
		glm::vec3(1),//scale
		"");
}

void TextDrawer::DrawSimpleText(Text text, Vector2 pos) {
	DrawSimpleText(text, pos, ALIN_CENTERED, ALT_CENTERED);
}

void TextDrawer::DrawSimpleText(Text text, Vector2 pos, Alineo alin) {
	DrawSimpleText(text, pos, alin, ALT_CENTERED);
}

void TextDrawer::DrawSimpleText(Text text, Vector2 pos, Altura alt) {
	DrawSimpleText(text, pos, ALIN_CENTERED, alt);
}


void TextDrawer::DrawSimpleText(Text text, Vector2 pos, Alineo alin, Altura alt) {
	if (text.text == "")
		return;
	Text::ChangeFont(text);
	SDL_Color color = text.color.ToSDL();
	SDL_Surface* surfaceMessage = TTF_RenderText_Blended(Text::usedFont, text.text.c_str(), color);


	auto colors = surfaceMessage->format->BytesPerPixel;

	GLenum textureFormat;
	if (colors == 4) {   // alpha
		if (surfaceMessage->format->Rmask == 0x000000ff)
			textureFormat = GL_RGBA;
		else
			textureFormat = GL_BGRA;
	}
	else {             // no alpha
		if (surfaceMessage->format->Rmask == 0x000000ff)
			textureFormat = GL_RGB;
		else
			textureFormat = GL_BGR;
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &rectM.texture);
	glBindTexture(GL_TEXTURE_2D, rectM.texture);

	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surfaceMessage->w, surfaceMessage->h, 0,
		textureFormat, GL_UNSIGNED_BYTE, surfaceMessage->pixels);


	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0); 
	
	SDL_Rect Message_rect;

	TTF_SizeText(Text::usedFont, text.text.c_str(), &Message_rect.w, &Message_rect.h);

	Message_rect.x = pos.x + (alin == 0 ? 0 : (alin == 1 ? -Message_rect.w / 2 : -Message_rect.w));
	Message_rect.y = pos.y + (alt == 0 ? 0 : (alt == 1 ? -Message_rect.h / 2 : -Message_rect.h));

	rect = RectP(glm::vec3(Message_rect.x, Message_rect.y, 0), glm::vec3(Message_rect.x + Message_rect.w, Message_rect.y, 0),
		glm::vec3(Message_rect.x, Message_rect.y + Message_rect.h, 0), glm::vec3(Message_rect.x + Message_rect.w, Message_rect.y + Message_rect.h, 0),
		glm::vec3(255), glm::vec3(255), glm::vec3(255), glm::vec3(255));
	rectM.render(OpenGLClass::shaders[2]);
	SDL_FreeSurface(surfaceMessage);
	glDeleteTextures(1, &rectM.texture);

}

