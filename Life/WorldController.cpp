#include "stdafx.h"
#include "WorldController.h"


WorldController::WorldController(World* world)
{
	this->world = world;
}

void WorldController::StartLife(int iterationsCount) {
	SaveWorldsPicture();
	for (size_t i = 0; i < iterationsCount; i++)
	{
		MakeWolrdIteration();
		SaveWorldsPicture();
	}
}

void WorldController::MakeWolrdIteration() {
	std::vector<bool> newWorldVector;
	for (size_t i = 0; i < world->worldVector.size(); i++)
	{
		int neighboardsCount = GetNeighboardsCountForFieldNumber(i);
		if (world->worldVector[i]) {//field is inhabited
			if (neighboardsCount == 2 || neighboardsCount == 3) {// field surwive
				newWorldVector.push_back(true);
			}
			else
			{
				newWorldVector.push_back(false);
			}
		}
		else
		{
			if (neighboardsCount == 3) {
				newWorldVector.push_back(true);
			}
			else
			{
				newWorldVector.push_back(false);
			}
		}
	}
	world->worldVector = newWorldVector;
	world->iterationNumber++;
}

int WorldController::GetNeighboardsCountForFieldNumber(int fieldNumber) {
	int result = 0;
	int iStart = -1;
	int iEnd = 2;
	int jStart = -1;
	int jEnd = 2;
	if (fieldNumber < world->worldSize) {
		iStart = 0;
	}
	if (fieldNumber > world->worldSize*world->worldSize - world->worldSize) {
		iEnd = 1;
	}
	if (fieldNumber% world->worldSize == 0) {
		jStart = 0;
	}
	if (fieldNumber% world->worldSize == world->worldSize - 1) {
		int jEnd = 1;
	}
	for (int i = iStart; i < iEnd; i++)
	{
		for (int j = jStart; j < jEnd; j++)
		{
			int pointer = fieldNumber + (world->worldSize*i) + j;
			if (pointer >= 0 && pointer < world->worldVector.size() && pointer != fieldNumber && world->worldVector[pointer]) {
				result++;
			}
		}
	}

	return result;
}

void WorldController::ShowWorldOnScreen() {
	for (size_t i = 0; i < world->worldSize; i++)
	{
		for (size_t j = 0; j < world->worldSize; j++)
		{
			printf(world->worldVector[world->worldSize*i + j] ? " X" : " 0");
		}
		printf("\n");
	}
	printf("\n");
}

void WorldController::SaveWorldsPicture() {
	std::stringstream ss;
	ss << "C:\\Users\\Totalit\\Desktop\\Life\\iteration" << world->iterationNumber << ".ppm";
	std::string path = ss.str();
	std::ofstream img(path);
	img << "P3" << std::endl;
	img << world->worldSize << " " << world->worldSize << std::endl;
	img << 255 << std::endl;

	for (size_t i = 0; i < world->worldSize; i++)
	{
		for (size_t j = 0; j < world->worldSize; j++)
		{
			if (world->worldVector[world->worldSize*i + j]) {
				img << 0 << " " << 0 << " " << 0 << std::endl;
			}
			else
			{
				img << 255 << " " << 255 << " " << 255 << std::endl;
			}
		}
	}
}

void WorldController::InitializeHalfTop() {
	for (size_t i = 0; i < world->worldSize*world->worldSize / 2; i++) {
		world->worldVector[i] = true;
	}
}

void WorldController::InitializeRandom20Percent() {
	for (size_t i = 0; i < world->worldSize*world->worldSize / 5; i++) {
		// very beauty
		//long random = 0 + (rand() % static_cast<long>(world->worldSize*world->worldSize + 1));
		//long random2 = 0 + (rand() % static_cast<long>(5));
		//world->worldVector[((random*10)% (world->worldSize*world->worldSize))+ random2] = true;
		long summ = 0;
		for (size_t i = 0; i < 10; i++)
		{
			long random = 0 + (rand() % static_cast<long>(world->worldSize*world->worldSize + 1));
			summ += random;
		}
		world->worldVector[((summ) % (world->worldSize*world->worldSize))] = true;

	}
}

std::vector<World*> WorldController::SplitByRows(int worldsCount) {
	std::vector<World*> vector;
	long worldsIndex = 0;
	for (size_t i = 0; i < worldsCount; i++)
	{
		if (i == 0 || i == worldsCount - 1) {
			World* worldTemp = new World(world->worldSize, world->worldSize / worldsCount + 1);
			for (size_t j = 0; j < worldTemp->height* worldTemp->width; j++)
			{
				worldTemp->worldVector[j] = world->worldVector[worldsIndex];
				worldsIndex++;
			}
			vector.push_back(worldTemp);
			worldsIndex -= worldTemp->width * 2;
		}
		else
		{
			World* worldTemp = new World(world->worldSize, world->worldSize / worldsCount + 2);
			for (size_t j = 0; j < worldTemp->height* worldTemp->width; j++)
			{
				worldTemp->worldVector[j] = world->worldVector[worldsIndex];
				worldsIndex++;
			}
			vector.push_back(worldTemp);
			worldsIndex -= worldTemp->width * 2;
		}


	}

	return vector;
}

World* WorldController::JoinRows(std::vector<World*> worldsVector) {
	World* world = new World(worldsVector[0]->width);
	world->worldSize = worldsVector[0]->width;
	int index = 0;
	for (size_t i = 0; i < worldsVector[0]->width*(worldsVector[0]->height - 1); i++)
	{
		world->worldVector[index] = (worldsVector[0]->worldVector[i]);
		index++;
	}
	for (size_t j = 1; j < worldsVector.size() -1; j++)
	{
		for (size_t i = worldsVector[j]->width; i < worldsVector[j]->width*(worldsVector[j]->height - 1); i++)
		{
			world->worldVector[index] = (worldsVector[j]->worldVector[i]);
			index++;
		}
	}
	for (size_t i = worldsVector[worldsVector.size()-1]->width; i < worldsVector[worldsVector.size() - 1]->width*worldsVector[worldsVector.size() - 1]->height; i++)
	{
		world->worldVector[index]=(worldsVector[worldsVector.size() - 1]->worldVector[i]);
		index++;
	}

	return world;
}

WorldController::~WorldController()
{
}
