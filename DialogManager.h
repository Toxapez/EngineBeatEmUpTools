#pragma once
#include "GameObject.h"
#include <iostream>
#include <fstream>
#include <locale.h>

struct DialogLine {
	std::string chara;
	std::string audiofile;
	std::string dLine;
	DialogLine(std::string chara, std::string audiofile, std::string dLine) 
		: chara(chara) , audiofile(audiofile), dLine(dLine)  {}
};

struct Dialog {
	std::string name;
	std::vector<DialogLine> dialoglines;
	Dialog() {};
	Dialog(std::string name) : name(name) {}
};

struct DialogManager
{
	DialogManager();
	std::map<std::string, Dialog> dialogs;
};

