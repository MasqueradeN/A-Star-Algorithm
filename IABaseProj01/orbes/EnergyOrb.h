#pragma once
#include "../raylib/raylib.h"
#include "../entorno/Grid.h"
#include <vector>

class EnergyOrb
{
public:
	EnergyOrb();

	void Initialize(int x, int y);
	void Update();
	void Render();
	void End();

	VectorInt2 GetPosition() { return mPos; }

private:
	Texture2D mTexture;
	//Rectangle mRect;
	VectorInt2 mPos;

};

