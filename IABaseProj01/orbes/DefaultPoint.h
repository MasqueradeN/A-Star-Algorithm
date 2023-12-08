#pragma once
#include "../raylib/raylib.h"

class DefaultPoint
{
public:
	DefaultPoint();

	void Initialize(int x, int y);
	void Update();
	void Render();
	void End();

	int* GetPosition() { return mPos; }

private:
	Texture2D mTexture;
	//Rectangle mRect;
	int mPos[2];

};

