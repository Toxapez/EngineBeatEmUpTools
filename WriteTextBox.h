#pragma once
#include "TextBox.h"
class WriteTextBox : public TextBox
{
	
	string::iterator pencil;
	string textQueue;
	int counter;
public:
	int writeSpeed;
	bool ended;
	WriteTextBox();
	WriteTextBox(Vector2 offset, Rect rContainer);
	void AddText(string);
	void Write(float speed = 1);
	
};


