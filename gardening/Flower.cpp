#include "Flower.h"
#include "GroundTile.h"
Flower::Flower()
{
	count = 0;
	minDistance = 0;
	numberOfFlowersPlanted = 0;

}

void Flower::init()
{
	TilesPlanted = new GroundTile[count];
}
void Flower::PlantFlower(GroundTile tile)
{
	TilesPlanted[numberOfFlowersPlanted] = tile;
	numberOfFlowersPlanted++;
}
