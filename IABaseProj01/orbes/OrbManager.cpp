#include "OrbManager.h"
//#include "../raylib/raymath.h"
#include "../entorno/Grid.h"
#include <random>
//#include <iostream>

OrbManager::OrbManager()
{
}

bool checkForAdjacents(int x, int y)
{
	sCell info[9] = {
		Grid::GetCell(x, y + 1),
		Grid::GetCell(x, y),
		Grid::GetCell(x, y - 1),
		Grid::GetCell(x - 1, y + 1),
		Grid::GetCell(x - 1, y),
		Grid::GetCell(x - 1, y - 1),
		Grid::GetCell(x + 1, y + 1),
		Grid::GetCell(x + 1, y),
		Grid::GetCell(x + 1, y - 1)
	};

	for (int cel = 0; cel < 9; cel++) {
		if (info[cel].object != eObjType::none) {
			info[cel].object != eObjType::energyorb;
			return true;
		}
	}
	return false;
}

void OrbManager::Initialize()
{
	//mOrbes
	std::random_device dev;
	std::mt19937 rng(dev());
	int col = Grid::GetMaxCol();
	int row = Grid::GetMaxRow();
	std::uniform_int_distribution<std::mt19937::result_type> distCol(0, col);
	std::uniform_int_distribution<std::mt19937::result_type> distRow(0, row);

	for (int i = 0; i < 10; i++)	{
		bool bSearch = true;
		while (bSearch) {
			int rnX = distCol(rng);
			int rnY = distRow(rng);
			if (!checkForAdjacents(rnX, rnY)) {
				EnergyOrb noeOrb;
				noeOrb.Initialize(rnX, rnY);
				mOrbes.push_back(noeOrb);
				mOrbesPos.push_back(noeOrb.GetPosition());
				bSearch = false;
			}
		}
	}

	bool bDefSrch = true;
	while (bDefSrch) {
		int rnX = distCol(rng);
		int rnY = distRow(rng);
		if (!checkForAdjacents(rnX, rnY)) {			
			bDefSrch = false;
		}
	}
}

void OrbManager::Update()
{
}

void OrbManager::Render()
{
	for (EnergyOrb& orb : mOrbes) {
		orb.Render();
	}
}

void OrbManager::End()
{
}

