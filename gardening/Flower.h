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
		void PlantFlower(GroundTile& tile);
		/// <summary>
		/// Checks if there are more flowers of this type left in the pool.
		/// </summary>
		/// <returns></returns>
		bool HasMore();
};

