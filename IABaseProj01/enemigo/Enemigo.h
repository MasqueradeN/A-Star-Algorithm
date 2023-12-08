#pragma once
#include "../raylib/raylib.h"
#include "../entorno/Barrera.h"
#include "../entorno/Borde.h"
#include "../entorno/Grid.h"
#include "../enemigo/AStar.h"
#include "../Node.h"
#include <vector>

enum class sMoveResultE {
	gook = 0,
	arrived,
	stoped,
};

enum class eActionE {
	none = 0,
	astar,
	move,
};

enum class eStateActionE {
	start = 0,
	astar,
	findAgent,
	findOrb,
	move
};

class Enemigo
{
public:
	Enemigo();

	void Initialize(int scW, int scH);
	void Update(float deltaTime, VectorInt2 agentPos);
	void Render();
	void End();

	void StateClick() { bStClk = true; }

	void SetTarget(int x, int y);
	void SetPosition(int x, int y);

	void SetBarriers(const std::vector<Barrera> &barreras);
	void SetOrbs(std::vector<VectorInt2>& orbsPos);

	VectorInt2 GetEnemyPosition();

private:
	//Vector2 GetInternalPosition();

	sMoveResultE GoTo(float deltaTime);
	void Translate(int dx, int dy);
	//void Rotate(float dangle);

	bool checkForBarriers(const VectorInt2& realPos);

	Texture2D mTexture;

	VectorInt2 mPosition;
	VectorInt2 mTarget;
	std::vector<VectorInt2> orbs;

	float mTime;
	std::vector<Barrera> mBarriers;
	std::vector<Borde> mBordes;

	eActionE mAction;
	eStateActionE mStateAction;
	bool bStClk;

	int turnCounter = 3;

	AStar mAStar;
};

