#include "TextBox.h"

TextBox::TextBox() {}

TextBox::TextBox(Vector2 offset, Rect rContainer, Color c, Color bgc) : bgColor(bgc) {
	rectColor = c;
	offsetMark = offset;
	originalMarkRect = rContainer;
	SetOffSetMark(offset, rContainer);
	alineo = ALIN_LEFT;
	refPos = nullptr;
}

TextBox::TextBox(Text t, Vector2 offset, Rect rContainer, Color c, Color bgc ) : bgColor(bgc) {
	displayText = t;
	offsetMark = offset;
	originalMarkRect = rContainer;
	SetOffSetMark(offset,rContainer);
	rectColor = c;
	alineo = ALIN_LEFT;
	refPos = nullptr;
}

void TextBox::SetOffSetMark(Vector2 offset, Rect rContainer) {
	markRect = rContainer;
	containerRect = Rect(Vector2(rContainer.x + offset.x, rContainer.y + offset.y), 
		Vector2(rContainer.w - offset.x, rContainer.h - offset.y));
}
void TextBox::SetOffSetMark() {
	Vector2 offset = offsetMark ;
	Rect rContainer = originalMarkRect;
	markRect = rContainer;
	containerRect = Rect(Vector2(rContainer.x + offset.x, rContainer.y + offset.y) * SDLClass::screenWidthStreching,
		Vector2(rContainer.w - offset.x, rContainer.h - offset.y));
}

void TextBox::Draw() {
	if (refPos) 
		SetOffSetMark(offsetMark, originalMarkRect + *refPos + pos);
	else SetOffSetMark(offsetMark, originalMarkRect + pos);
	markRect.Pos(Vector2(containerRect.x - offsetMark.x, containerRect.y - offsetMark.y));
	if(bgColor.r != -1)
		FigureDrawer::DrawFillRect(markRect, bgColor);
	if (rectColor.r != -1)
		FigureDrawer::DrawRect(markRect, rectColor);
	if(alineo == ALIN_LEFT)
		fitTextLinesLeft(displayText.text, Rect(0,0,containerRect.w, containerRect.h));
	else if (alineo == ALIN_CENTERED)
		fitTextLinesCentered(displayText.text, Rect(0, 0, containerRect.w, containerRect.h));
	
}

void TextBox::fitTextLinesLeft(string text, Rect rText) {

	if (!displayText.text.empty() && rText.w > 10) {
		Rect originalRText = rText;
		if (camDependent) {
			rText.w *= Cam::currentCam->zoom;
			rText.h *= Cam::currentCam->zoom;
			rText.x -= rText.w / 2;
			rText.y -= rText.h / 2;
		}
		Text t = displayText;
		t.camDependent = camDependent;
		t.size = displayText.size;
		Text::ChangeFont(t);
		SDL_Rect Message_rect;
		string r = text;
		string leftovers;
		TTF_SizeText(Text::usedFont, r.c_str(), &Message_rect.w, &Message_rect.h);
		while (Message_rect.w > rText.w) {
			do {
				leftovers.insert(leftovers.begin(),r.back());
				r.pop_back();
				if (r.empty()) { break; }
			} while (!(r.back() == ' '));
			TTF_SizeText(Text::usedFont, r.c_str(), &Message_rect.w, &Message_rect.h);
			if (r.empty()) {
				r.swap(leftovers);
				break;
			}
		}
		t.text = r;
		TextDrawer::DrawSimpleText(t, Vector2(rText.x + containerRect.x, rText.y + containerRect.y), TextDrawer::ALIN_LEFT, TextDrawer::ALT_UP);
		if (!leftovers.empty()) {
			Rect rect = originalRText;
			rect.y += Message_rect.h + 5;
			fitTextLinesLeft(leftovers, rect);
		}
		else {
			endLine = Rect(originalRText.x+ Message_rect.w, originalRText.y, originalRText.x + Message_rect.w, originalRText.y + Message_rect.h);

		}
	}
}

void TextBox::fitTextLinesCentered(string text, Rect rText) {

	if (!displayText.text.empty() && rText.w > 10) {
		Text::ChangeFont(displayText);
		SDL_Rect Message_rect;
		string r = text;
		string leftovers;
		TTF_SizeText(Text::usedFont, r.c_str(), &Message_rect.w, &Message_rect.h);
		while (Message_rect.w > rText.w) {
			do {
				leftovers.insert(leftovers.begin(), r.back());
				r.pop_back();
				if (r.empty()) { break; }
			} while (!(r.back() == ' '));
			TTF_SizeText(Text::usedFont, r.c_str(), &Message_rect.w, &Message_rect.h);
			if (r.empty()) {
				r.swap(leftovers);
			}
		}
		Text t = displayText;
		t.text = r;
		t.size = displayText.size;
		TextDrawer::DrawSimpleText(t, Vector2(rText.x + containerRect.x+ rText.w/2, rText.y + containerRect.y),  TextDrawer::ALIN_CENTERED);
		if (!leftovers.empty()) {
			Rect rect = rText;
			rect.y += Message_rect.h + 5;
			fitTextLinesCentered(leftovers, rect);
		}
		else {
			endLine = Rect(rText.x + Message_rect.w, rText.y, rText.x + Message_rect.w, rText.y + Message_rect.h);

		}
	}
}