#include "WriteTextBox.h"

WriteTextBox::WriteTextBox() {
	writeSpeed = 3;
	counter = 0;
	ended = true;
}

WriteTextBox::WriteTextBox(Vector2 offset, Rect rContainer) : TextBox(offset, rContainer){
	writeSpeed = 3;
	counter = 0;
	ended = true;
}

void WriteTextBox::AddText(string text) {
	textQueue = text;
	pencil = textQueue.begin();
	displayText.text.clear();
	ended = false;
}

void WriteTextBox::Write(float speed) {
	counter += speed;
	if (!ended && counter >= writeSpeed) {
		counter = 0;
		displayText.text.push_back(*pencil);
		pencil++;
		if (pencil == textQueue.end()) {
			ended = true;
		}
	}
}