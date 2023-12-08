#pragma once
#include "../raylib/raylib.h"

class Borde
{
public:
	Borde();

	void Initialize(int x, int y, int w, int h);
	void Update();
	void Render();
	void End();

private:
	Rectangle mRect;


};

