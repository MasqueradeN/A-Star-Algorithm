#pragma once
#include "../raylib/raylib.h"
#include "Grid.h"
#include "Barrera.h"
#include "Borde.h"
#include <vector>

class EntornoMgr
{
public:
	EntornoMgr();

	void Initialize(int scW, int scH);
	void Update();
	void Render();
	void End();

	void AddBorder();
	std::vector<VectorInt2> AddEscena01();

private:
	int maxW, maxH;
	bool hasBorder;

	std::vector<Borde> mBordes;
	std::vector<Barrera> mBarreras;
};

