#pragma once
#include "../raylib/raylib.h"
#include "../entorno/Grid.h"
#include <vector>

class Shooter
{
public:
	Shooter() = default;

	sCell getRayHit(Vector2 p0, Vector2 dir);

	std::vector<sCell> getRayHitsPattern1(Vector2 p0, Vector2 dir);


private:
	int mNumRays = 10;
	float mAngCvr = 30.f;

};

