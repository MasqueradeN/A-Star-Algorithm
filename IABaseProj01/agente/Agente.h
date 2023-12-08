#pragma once
#include "../raylib/raylib.h"
#include "../entorno/Barrera.h"
#include "../entorno/Grid.h"
#include "Shooter.h"
#include <vector>

struct Kinematic 
{
	Vector2 position;
	Vector2 orientation;
	//float rotation;
};

struct SteeringOutput
{
	VectorInt2 linear;
	float angular;
};

enum class sMoveResult {
	gook = 0,
	arrived,
	stoped,
};

enum class eAction {
	none = 0,
	rayos,
	move,
};

enum class eStateAction {
	start = 0,
	shoot,
	selAny,
	selEnemy,
	selOrb,
	selBack,
	move
};

class Agente
{
public:
	Agente();

	void Initialize(int scW, int scH);
	void Update(float deltaTime);
	void Render();
	void End();

	void StateClick() { bStClk = true; }

	void SetTarget(int x, int y);
	void SetPosition(int x, int y);

	void SetBarriers(const std::vector<Barrera> &barreras);

	VectorInt2 GetAgentPosition();
	float GetAgentRotation();

private:
	Vector2 GetInternalPosition();

	sMoveResult GoTo(float deltaTime);
	void Translate(float damount);
	void Rotate(float dangle);

	bool checkForBarriers(const Vector2& realPos);

	void selectAny(std::vector<sCell> &hitcls);
	bool select(std::vector<sCell>& hitcls, eObjType type);

private:
	Texture2D mTexture;

	Kinematic mCineman;
	SteeringOutput mManejo;
	
	Vector2 deltaPos;
	float deltaAng;

	float mTime;
	VectorInt2 mTarget;

	std::vector<Barrera> mBarriers;

	eAction mAction;
	eStateAction mStateAction;
	bool bStClk;

	Shooter mShooter;
};

