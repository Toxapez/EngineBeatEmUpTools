#include "Level.h"

Level::Level() {
	SetName("tName");
	for (int i = 0; i < LEVELSIZEY; i++) {
		for (int j = 0; j < LEVELSIZEX; j++) {
			for (int k = 0; k < nLevelLayers; k++)
			{
				levelLayers[k].content[i][j] = EMPTYTILEVALUE;
			}
		}
	}
	for (int i = 0; i < LEVELSIZEY; i++) {
		for (int j = 0; j < LEVELSIZEX; j++) {
			for (int k = 0; k < nLevelWaves; k++)
			{
				waves[k].content[i][j] = EMPTYTILEVALUE;
			}
		}
	}
	nWaves = 0;
}

void Level::SetName(const char* tName) {
	for (int i = 0; i < 30; i++) {
		name[i] = tName[i];
	}
}

void Level::Save(std::vector<std::string>* config, std::vector<std::string>* waveconfig, std::vector < std::vector<int>> glosario) {
	std::ofstream file("levels/" + std::string(name) + ".lvl");
	if (file.is_open())
	{
		file.write((char*)this, sizeof(Level));
		file.close();
		//config
		std::ofstream file2("levels/" + std::string(name) + ".config");
		if (file2.is_open())
		{
			for (int i = 0; i < config->size(); i++)
			{
				file2 << (*config)[i] << "\n";
			}
			
			file2.close();
		}

		std::ofstream file3("levels/" + std::string(name) + ".wconfig");
		if (file3.is_open())
		{
			for (int j = 0; j < nLevelWaves + 1; j++)
			{
				file3 << waveconfig[j].size() << "\n";
				for (int i = 0; i < waveconfig[j].size(); i++)
					file3 << waveconfig[j][i] << "\n";
			}

			file3.close();
		}
		std::ofstream file4("levels/" + std::string(name) + ".glog");
		if (file4.is_open())
		{
			for (int j = 0; j < glosario.size(); j++)
			{
				for (int i = 0; i < glosario[j].size(); i++)
					file4 << glosario[j][i] << "\t";
				file4 << "\n";
			}

			file4.close();
		}
		
	}
	else std::cout << "Unable to create file";
}

void Level::Load(std::string n, std::vector<std::string>* config, std::vector<std::string>* waveconfig, std::vector < std::vector<int>>* glosario) {
	std::ifstream file("levels/" + std::string(n)+ ".lvl");
	if (file)
	{
		file.read((char*)this, sizeof(Level));
		file.close();
		std::ifstream file2("levels/" + std::string(n) + ".config");
		std::string str;
		config->clear();
		while (getline(file2, str))
		{
			config->push_back(str);
		}

		std::ifstream file3("levels/" + std::string(n) + ".wconfig");
		for (int j = 0; j < nLevelWaves + 1; j++)
		{
			waveconfig[j].clear();
			getline(file3, str);
			int waveSize = stoi(str);
			for (int i = 0; i < waveSize; i++) {
				getline(file3, str);
				waveconfig[j].push_back(str);
			}
		}
		std::ifstream file4("levels/" + std::string(n) + ".glog");
		int j = 0;
		while (getline(file4, str))
		{
			std::string segment;
			std::stringstream test(str);
			while (std::getline(test, segment, '\t'))
			{
				(*glosario)[j].push_back(std::stoi(segment));
			}
			j++;
		}
		
	}
	else std::cout << "Unable to open file";
}

void Level::Delete() {
	std::ifstream file("levels/" + std::string(name) + ".lvl");
	if (file)
	{
		file.close();
		remove(("levels/" + std::string(name) + ".lvl").c_str());
	}
	else std::cout << "Unable to delete file";
}