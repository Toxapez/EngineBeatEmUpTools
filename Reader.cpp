#include "Reader.h"

std::vector<std::string*>* Reader::vars;
std::string Reader::fullfile;
int Reader::charReaded;

void Reader::SetReader(std::string filename, std::vector<std::string*>* v) {
	std::string path = filename;
	std::ifstream input_file(filename);
	fullfile = std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
	vars = v;
	charReaded = 0;
}

bool Reader::Read() {
	std::string buffer;

	std::string* parts = new std::string[vars->size()];
	int p = 0;
	while (p < vars->size())
	{
		while (fullfile[charReaded] != '\t' && fullfile[charReaded] != '\n' && !IsFinished())
		{
			buffer.push_back(fullfile[charReaded++]);
		}
		charReaded++;
		*(*vars)[p++] = buffer;
		buffer.clear();
	}
	return IsFinished();
}

bool Reader::IsFinished() {
	return !(charReaded < fullfile.size());
}