#include "EntornoMgr.h"
#include "../raylib/raymath.h"

#include <cmath>
#include <iostream>

const int stdBorde = 2;

EntornoMgr::EntornoMgr()
{
}

void EntornoMgr::Initialize(int scW, int scH)
{
	maxW = scW;
	maxH = scW;
}

void EntornoMgr::Update()
{
}

void EntornoMgr::Render()
{
	for (Barrera& barr : mBarreras) {
		barr.Render();
	}
	for (Borde& barr : mBordes) {
		barr.Render();
	}
}

void EntornoMgr::End()
{
}

void EntornoMgr::AddBorder()
{
	VectorInt2 dim = Grid::GetGridCoords({ (float)maxW, (float)maxH });
	Borde top, right, left, bottom;
	top.Initialize(0, 0, dim.x, stdBorde);
	right.Initialize(dim.x - stdBorde, stdBorde, stdBorde, dim.y - 2 * stdBorde);
	left.Initialize(0, stdBorde, stdBorde, dim.y - 2 * stdBorde);
	bottom.Initialize(0, dim.y - stdBorde, dim.x, stdBorde);
	
	mBordes.push_back(top);
	mBordes.push_back(right);
	mBordes.push_back(left);
	mBordes.push_back(bottom);
}

std::vector<VectorInt2> EntornoMgr::AddEscena01()
{
	VectorInt2 dim = Grid::GetGridCoords({ (float)maxW, (float)maxH });
	Barrera sceneb[4];
	sceneb[0].Initialize(dim.x / 2 - 3, dim.y / 5, 6, dim.y / 5);
	sceneb[1].Initialize(dim.x / 5, dim.y / 4, dim.y / 5, 6);
	sceneb[2].Initialize(3 * dim.x / 5, dim.y / 4, dim.y / 5, 6);
	sceneb[3].Initialize(dim.x / 2 - 3, 3 * dim.y / 5, dim.y / 5, 6);
	for (int i = 0; i < 4; i++)	{ mBarreras.push_back(sceneb[i]); }

	VectorInt2 vecAgente = { 70, 4 * dim.y / 5 };
	VectorInt2 vecEnemigo = { 7, 20 };

	return std::vector<VectorInt2>{vecAgente, vecEnemigo};
}
