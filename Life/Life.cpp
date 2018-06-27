// Life.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "World.h"
#include <vector>
#include "WorldController.h"


int main()
{
	int worldsSize = 10;
	int iterations = 100;
	int splitCount = 5;
	World* world = new World(worldsSize);
	WorldController* wC = new WorldController(world);

	wC->InitializeRandom20Percent();
	//wC->StartLife(1);
	for (size_t i = 0; i < iterations; i++)
	{
		std::vector<World*> vector = wC->SplitByRows(splitCount);
		//section below can be execute parallel
		for (size_t i = 0; i < vector.size(); i++)
		{
			WorldController* wC2 = new WorldController(world);
			wC2->MakeWolrdIteration();
		}
		//
		World* world2 = wC->JoinRows(vector);
		WorldController* wC3 = new WorldController(world2);
		wC3->SaveWorldsPicture();
	}
	int a = 5;

	return 0;
}

