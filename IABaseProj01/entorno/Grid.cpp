#include "Grid.h"
#include "../raylib/raymath.h"
#include <cmath>
#include <iostream>

const int stdSqr = 10;

std::vector<std::vector<sCell>> Grid::mGrid;
int Grid::maxCol = 0;
int Grid::maxRow = 0;

void Grid::Initialize(int scW, int scH)
{
	maxCol = static_cast<int>(scW / stdSqr);
	maxRow = static_cast<int>(scH / stdSqr);	
	mGrid.resize(maxCol, std::vector<sCell>(maxCol, { eObjType::none }));
}

sCell Grid::GetCell(int x, int y)
{
	boundCoords(x, y);
	return mGrid[x][y];
}


void Grid::SetCell(int x, int y, sCell value)
{
	boundCoords(x, y);
	mGrid[x][y] = value;
}

void Grid::boundCoords(int& x, int& y)
{
	if (x > maxCol - 1) { x = maxCol - 1; }
	if (x < 0) { x = 0; }
	if (y > maxRow - 1) { y = maxRow - 1; }
	if (y < 0) { y = 0; }
}

Vector2 Grid::GetRealCoords(int x, int y)
{
	return Vector2{
		(float)x * stdSqr,
		(float)y * stdSqr };
}

VectorInt2 Grid::GetGridCoords(Vector2 pos)
{
	int x = static_cast<int>(floorf(pos.x / stdSqr));
	int y = static_cast<int>(floorf(pos.y / stdSqr));
	return VectorInt2{ x, y };
}

Vector2 Grid::GetSnapCoords(Vector2 pos)
{
	return Vector2{
		floorf(pos.x / stdSqr) * stdSqr,
		floorf(pos.y / stdSqr)* stdSqr
	};
}

