#include "EnergyOrb.h"
//#include "../raylib/raymath.h"
#include "../entorno/Grid.h"
//#include <cmath>
#include <iostream>

EnergyOrb::EnergyOrb()
	: mPos{ 0 }
{
}

void EnergyOrb::Initialize(int x, int y)
{
	mTexture = LoadTexture("resources/orbe.png");

	mPos.x = x;
	mPos.y = y;
}

void EnergyOrb::Update()
{
}

void EnergyOrb::Render()
{

	Vector2 rnrPos = Grid::GetRealCoords(mPos.x, mPos.y);
	DrawTexture(mTexture, rnrPos.x, rnrPos.y, WHITE);
}

void EnergyOrb::End()
{
}
