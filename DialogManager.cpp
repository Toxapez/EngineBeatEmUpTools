#include "DialogManager.h"



DialogManager::DialogManager() {
	setlocale(LC_ALL, "");
	std::string path = std::string("assets/dialog/01.tsv");
	std::ifstream input_file(path);
	std::string fullfile = std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());

	int k = 0;
	std::string buffer;
	std::string parts[3];
	int p = 0;
	Dialog d;
	while (k < fullfile.size()) {
		if (fullfile[k] != '\t') {
			if (fullfile[k] == '\n') {
				if (buffer != "") {
					parts[p] = buffer;
					buffer.clear();
					p++;
				}
				else if (p == 2) {
					parts[p] = buffer;
					buffer.clear();
					p++;
				}
			}
			else buffer.push_back(fullfile[k]);
		}
		else {
			if (fullfile[k] == '\t') {
				if (buffer != "") {
					parts[p] = buffer;
					buffer.clear();
					p++;
				}
				else {
					p = 0;
					buffer.clear();
					if (!d.dialoglines.empty()) {
						dialogs.insert(std::pair<std::string,Dialog>(d.name,d));
					}
					d = Dialog(parts[0]);
				}
			}
			else {
				if (p < 3) {
					parts[p] = buffer;
					buffer.clear();
					p++;
				}
			}

		}
		if (p == 3) {
			d.dialoglines.push_back(DialogLine(parts[0], parts[1], parts[2]));
			for (int i = 0; i < 3; i++)
				parts[i].clear();
			p = 0;
		}
		k++;
	}
	if (!d.dialoglines.empty()) {
		dialogs.insert(std::pair<std::string, Dialog>(d.name, d));
	}
}
