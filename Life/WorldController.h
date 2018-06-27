#include "World.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <random>
#pragma once
class WorldController
{
	World* world;
public:
	WorldController(World* world);
	void StartLife(int iterationsCount);
	void MakeWolrdIteration();
	int GetNeighboardsCountForFieldNumber(int fieldNumber);
	void ShowWorldOnScreen();
	void SaveWorldsPicture();
	void InitializeHalfTop();
	void InitializeRandom20Percent();
	std::vector<World*> SplitByRows(int worldsCount);
	World* JoinRows(std::vector<World*> worldsVector);
	~WorldController();
};

