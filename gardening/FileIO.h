#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include <filesystem>

using namespace std;

bool loadFileData(string* (&fileData), string filePath, int& count);
bool readFiles(string gardenfile = "", string flowerfile = "");
