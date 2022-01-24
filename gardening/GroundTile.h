#pragma once


using namespace std;
class GroundTile
{

public:
	GroundTile(void);
	bool isBlocked;
	bool isFlowerPlanted;
	char* FlowerName;
	int tile_x, tile_y;
};

