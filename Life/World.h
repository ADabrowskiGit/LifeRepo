#include <vector>
#pragma once
class World
{

public:
	int worldSize, width, height;
	int iterationNumber;
	std::vector<bool> worldVector;
	World(int worldSize);
	World(int w, int h);
	~World();
};

