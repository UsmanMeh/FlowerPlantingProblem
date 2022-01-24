#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include "Flower.h"
#include <filesystem>

using namespace std;

bool loadFileData(string* (&fileData), string filePath, int& count);
bool readFiles(string gardenfile = "", string flowerfile = "");
void plantFlowers();