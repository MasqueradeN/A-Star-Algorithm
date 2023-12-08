#include "Borde.h"
#include "../raylib/raymath.h"
#include "Grid.h"
#include <cmath>
#include <iostream>

const Color bordeColor = Color{ 255, 121, 91, 255 };

Borde::Borde()
{
}

void Borde::Initialize(int x, int y, int w, int h)
{
	Vector2 pos = Grid::GetRealCoords(x, y);
	Vector2 dim = Grid::GetRealCoords(w, h);	
	mRect = Rectangle{ pos.x,	pos.y, dim.x,	dim.y };

	for (int row = 0; row < h; row++)	{
		for (int col = 0; col < w; col++)	{
			Grid::SetCell(x + col, y + row, 
				sCell{ eObjType::borde, x + col, y + row });
		}
	}
}

void Borde::Update()
{
}

void Borde::Render()
{
	DrawRectangleRec(mRect, bordeColor);
}

void Borde::End()
{
}
