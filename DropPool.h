#pragma once
#include "Recolectables.h"

struct BingoSphere {
	std::vector<std::string> names;
	std::vector<int> weights;
	std::vector<int> nsss;
	int totalWeight = 0;
	void Add(std::string n, int w, int nss = -1) {
		names.push_back(n);
		weights.push_back(w);
		totalWeight += w;
		nsss.push_back(nss);
	}
	void take(std::string* str, int* nss) {
		int r = rand() % totalWeight;
		int countedWeight = 0;
		for (int i = 0; i < weights.size(); i++) {
			countedWeight += weights[i];
			if (r < countedWeight) {
				*str = names[i];
				*nss = nsss[i];
				return;
			}
		}
	}
};

struct DropPool
{
	static void DecideDrop(std::string poolName, Vector2 pos) {
		BingoSphere bS;
		if (poolName == "normalEnemy") {
			for (int i = 0; i < Recolectables::lesheShaboSS.nSlots; i++)
			{
				bS.Add("lesheShabo", 10, i);
			}
		}
		int nSS = -1;
		std::string dropName;
		bS.take(&dropName, &nSS);

		Recolectables::scoper.GetNextScope().Set(dropName, pos, nSS);
	}
};



