#pragma once
#include <string>
using namespace std;

class Map
{
public:
	Map();
	~Map();

	void LoadMap(string path, int sizeX, int sizeY);
	void DrawMap();

private:
	
};