#pragma once
//#include "../raylib/raylib.h"
#include "EnergyOrb.h"
#include <vector>

class OrbManager
{
public:
	OrbManager();

	void Initialize();
	void Update();
	void Render();
	void End();

	std::vector<EnergyOrb>& GetOrbes() { return mOrbes; }
	std::vector<VectorInt2>& GetOrbesPos() { return mOrbesPos; }

private:
	
	std::vector<EnergyOrb> mOrbes;
	std::vector<VectorInt2> mOrbesPos;

};

