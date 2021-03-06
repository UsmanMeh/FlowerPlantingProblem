// gardening.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "FileIO.h"
#include "gardening.h"
string *gardenLayoutData;
string *flowersData;
int gardenLayerCount = 0;
int tilesPerLayerCount = 0;
int flowersCount = 0;

Flower *flowers;
GroundTile** groundTiles;


int main()
{
	string BaseFolder = "..//gardening//gardeningDataFiles//";

	if (readFiles(BaseFolder + "garden4.txt",
		BaseFolder + "flowers4.txt"))
	{
		cout << endl << "Flowers Loaded" << endl;
		for (size_t i = 0; i < flowersCount; i++)
		{
			cout << "|Flower " << (i + 1) << endl;
			cout << "  |name = " << flowers[i].name << "\n";
			cout << "  |count = " << flowers[i].count << "\n";
			cout << "  |minDistance = " << flowers[i].minDistance << "\n";
		}
		cout << endl << "************" << endl << endl;
		cout << "Ground Loaded" << endl;
		for (size_t x = 0; x < gardenLayerCount; x++)
		{
			for (size_t y = 0; y < tilesPerLayerCount; y++)
			{
				if (groundTiles[x][y].isFlowerPlanted)
					cout << groundTiles[x][y].FlowerName;
				else if (groundTiles[x][y].isBlocked)
					cout << "X";
				else
					cout << " ";
			}
			cout << "\n";
		}
		cout << endl << "************" << endl << endl;
		//plantFlowers();
		PlantFlowersImproved();
		cout << "Flowers Planted" << endl;
		for (size_t x = 0; x < gardenLayerCount; x++)
		{
			for (size_t y = 0; y < tilesPerLayerCount; y++)
			{
				if (groundTiles[x][y].isFlowerPlanted)
					cout << groundTiles[x][y].FlowerName;
				else if (groundTiles[x][y].isBlocked)
					cout << "X";
				else
					cout << " ";
			}
			cout << "\n";
		}
	}
}
int manhattan_distance(int x1, int y1, int x2, int y2)
{
	double distance;
	int xDif, yDif;

	xDif = x2 - x1;
	yDif = y2 - y1;
	if (xDif < 0)
		xDif = -xDif;
	if (yDif < 0)
		yDif = -yDif;
	distance = xDif + yDif;
	//cout << "\n\nManhattan Distance between P1(" << x1 << "," << y1 << ") and P2(" << x2 << "," << y2 << ") : " << distance;
	return distance;
}
bool IsTileValid(int tileX, int tileY, Flower flowerToBePlanted)
{
	if(groundTiles[tileX][tileY].isBlocked || groundTiles[tileX][tileY].isFlowerPlanted)
		return false;
	if (flowerToBePlanted.numberOfFlowersPlanted == 0)
		return true;
	for (size_t i = 0; i < flowerToBePlanted.numberOfFlowersPlanted; i++)
	{
		if (manhattan_distance(tileX, tileY, flowerToBePlanted.TilesPlanted[i].tile_x, flowerToBePlanted.TilesPlanted[i].tile_y) > flowerToBePlanted.minDistance)
			return true;
	}
	return false;
}

void plantFlowers()
{
	for (size_t i = 0; i < flowersCount; i++)
	{
		for (size_t j = 0; j < flowers[i].count; j++)
		{	
			bool planted = false;
			for (size_t x= 0; x < gardenLayerCount && !planted; x++)
			{
				for (size_t y = 0; y < tilesPerLayerCount && !planted; y++)
				{
					if (IsTileValid(x, y, flowers[i]))
					{
						flowers[i].PlantFlower(groundTiles[x][y]);
						j++;
						if(j >= flowers[i].count)
							planted = true;
						continue;
					}
					
				}
			}
		}
	}
}

void PlantFlowersImproved()
{
	for (size_t x = 0; x < gardenLayerCount; x++)
	{
		for (size_t y = 0; y < tilesPerLayerCount; y++)
		{
			for (size_t i = 0; i < flowersCount; i++)
			{
				if (IsTileValid(x, y, flowers[i]) && flowers[i].HasMore())
				{
					flowers[i].PlantFlower(groundTiles[x][y]);
					continue;
				}
			}
		}
	}
}

bool loadFileData(string* (&fileData), string filePath, int& count)
{
	fstream myFile;
	myFile.open(filePath, ios::in);
	string line;
	if (!myFile) {
		cout << "File not found!";
		return 0;
	}
	else {
		cout << "File found successfully!\n";
		int numLines = 0;
		while (getline(myFile, line)) { //read data from file object and put it into string.
			numLines++;
		}
		count = numLines;
		fileData = new string[numLines];
		int index = 0;
		myFile.clear();
		myFile.seekg(0, ios::beg);
		while (getline(myFile, line)) { //read data from file object and put it into string.
			fileData[index] = line;
			//cout << line << "\n"; //print the data of the string
			//cout << fileData[index] << "\n"; //print the data of the string
			index++;
		}

		myFile.close();
		return 1;
	}
}

bool readFiles(string gardenfile, string flowerfile)
{
	string gardenFilePath = gardenfile;
	string flowersFilePath = flowerfile;
	if (gardenFilePath == "")
	{
		cout << "Please enter the garden Layout File Path";
		cin >> gardenFilePath;
	}
	if (flowersFilePath == "")
	{
		cout << "\nPlease enter flowers file path";
		cin >> flowersFilePath;
	}

	bool gardenFileDone = loadFileData(gardenLayoutData, gardenFilePath, gardenLayerCount);
	bool flowersFileDone = loadFileData(flowersData, flowersFilePath, flowersCount);

	flowers = new Flower[flowersCount];

	char* next_token;
	char* token;
	const char* delim = ",";

	groundTiles = new GroundTile*[gardenLayerCount];
	for (size_t i = 0; i < gardenLayerCount; i++)
	{
		char* input = const_cast<char*>(gardenLayoutData[i].c_str());
		tilesPerLayerCount = strlen(input);
		groundTiles[i] = new GroundTile[tilesPerLayerCount];
		for (size_t j = 0; j < tilesPerLayerCount; j++)
		{
			groundTiles[i][j].isBlocked = input[j] == 'X';
			groundTiles[i][j].isFlowerPlanted = false;
			groundTiles[i][j].tile_x = i;
			groundTiles[i][j].tile_y = j;
		}
	}

	for (size_t i = 0; i < flowersCount; i++)
	{
		char* input = const_cast<char*>(flowersData[i].c_str());
		token = strtok_s(input, delim, &next_token);
		flowers[i].name = token;
		token = strtok_s(NULL, delim, &next_token);
		flowers[i].count = atoi(token);
		token = strtok_s(NULL, delim, &next_token);
		flowers[i].minDistance = atoi(token);
		flowers[i].init();
	}

	return gardenFileDone && flowersFileDone;
}

