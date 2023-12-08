#pragma once
#include "../raylib/raylib.h"

class Barrera
{
public:
	Barrera();

	void Initialize(int x, int y, int w, int h);
	void Update();
	const void Render();
	void End();

private:
	Rectangle mRect;


};

