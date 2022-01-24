#pragma once
#include "GroundTile.h"

using namespace std;
class Flower
{
public:
		Flower(void);
		char* name;
		int count;
		int minDistance;
		int numberOfFlowersPlanted;
		GroundTile* TilesPlanted;

		void init();
		void PlantFlower(GroundTile tile);
};

