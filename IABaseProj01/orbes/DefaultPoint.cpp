#include "DefaultPoint.h"
//#include "../raylib/raymath.h"
#include "../entorno/Grid.h"
//#include <cmath>
#include <iostream>

DefaultPoint::DefaultPoint()
	: mPos{ 0 }
{
}

void DefaultPoint::Initialize(int x, int y)
{
	mTexture = LoadTexture("resources/mario.png");

	mPos[0] = x;
	mPos[1] = y;
}

void DefaultPoint::Update()
{
}

void DefaultPoint::Render()
{

	Vector2 rnrPos = Grid::GetRealCoords(mPos[0], mPos[1]);
	DrawTexture(mTexture, rnrPos.x, rnrPos.y, WHITE);
}

void DefaultPoint::End()
{
}
