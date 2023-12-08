#include "Barrera.h"
#include "../raylib/raymath.h"
#include "Grid.h"
#include <cmath>
#include <iostream>

const Color barrColor = Color{ 66, 138, 255, 255 };

Barrera::Barrera()
{
}

void Barrera::Initialize(int x, int y, int w, int h)
{
	Vector2 pos = Grid::GetRealCoords(x, y);
	Vector2 dim = Grid::GetRealCoords(w, h);	
	mRect = Rectangle{ pos.x,	pos.y, dim.x,	dim.y };

	for (int row = 0; row < h; row++)	{
		for (int col = 0; col < w; col++)	{
			Grid::SetCell(x + col, y + row, sCell{ eObjType::barrier });
		}
	}
}

void Barrera::Update()
{
}

const void Barrera::Render()
{
	DrawRectangleRec(mRect, barrColor);
}

void Barrera::End()
{
}
