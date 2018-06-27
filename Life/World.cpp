#include "stdafx.h"
#include "World.h"


World::World(int worldSize)
{
	this->worldSize = worldSize;
	iterationNumber = 0;
	for (size_t i = 0; i < worldSize*worldSize; i++)
	{
		worldVector.push_back(false);

	}
}

World::World(int w, int h) {
	width = w;
	height = h;
	iterationNumber = 0;
	for (size_t i = 0; i < width*height; i++)
	{
		worldVector.push_back(false);
	}
}


World::~World()
{
}
