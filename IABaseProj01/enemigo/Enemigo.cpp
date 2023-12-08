#include "Enemigo.h"
#include "../raylib/raymath.h"
#include "../entorno/Grid.h"
#include "../Node.h"
#include <cmath>
#include <iostream>

const float linearAcc = 0.01f; // per sec
const float angularAcc = 0.02f;

Enemigo::Enemigo()
	: mTime{ 0.f }, mAction(eActionE::none)
	, mStateAction(eStateActionE::start)
	, bStClk(false), mPosition{ 0,0 }
{
}

void Enemigo::Initialize(int scW, int scH)
{
	mTexture = LoadTexture("resources/doflamingo.png");

	int frameWidth = mTexture.width;
	int frameHeight = mTexture.height;
}

void Enemigo::Update(float deltaTime, VectorInt2 agentPos)
{
	std::vector<std::vector<sCell>> grid;
	std::vector<VectorInt2> thePath;
	switch (mStateAction)
	{
	case eStateActionE::start:
		mStateAction = eStateActionE::astar;
		std::cout << "en inicia" << std::endl;
		bStClk = false;
		break;
	case eStateActionE::astar: {
		if (bStClk) {
			std::cout << "en haciendo astar" << std::endl;
			Node* currentPos = new Node(mPosition.x, mPosition.y);
			Node* currentGoal = new Node(agentPos.x, agentPos.y);

			//sCell info[9] = {
			//	Grid::GetCell(mPosition.x, mPosition.y + 1),
			//	Grid::GetCell(mPosition.x, mPosition.y),
			//	Grid::GetCell(mPosition.x, mPosition.y - 1),
			//	Grid::GetCell(mPosition.x - 1, mPosition.y + 1),
			//	Grid::GetCell(mPosition.x - 1, mPosition.y),
			//	Grid::GetCell(mPosition.x - 1, mPosition.y - 1),
			//	Grid::GetCell(mPosition.x + 1, mPosition.y + 1),
			//	Grid::GetCell(mPosition.x + 1, mPosition.y),
			//	Grid::GetCell(mPosition.x + 1, mPosition.y - 1)
			//};
			//std::vector<sCell> nearGrid;

			//for (auto i = 0; i < 9; i++)
			//{
			//	nearGrid.push_back(info[i]);
			//}

			//std::vector<std::vector<sCell>> cells; //= Grid::mGrid;

			//for (auto i = 0; i < 9; i++)
			//{
			//cells.push_back(nearGrid);
			//}

			
			//grid.push_back(cells);
			std::vector<Node*> elAstar = mAStar.AStarSearch(currentPos, currentGoal, Grid::mGrid  /*cells*/, agentPos, orbs);

			
			for (Node* path : elAstar)
			{
				thePath.push_back(VectorInt2{ path->x, path->y });
			}
			bStClk = false;
			break;
		}
	} break;
	case eStateActionE::move:
		if (bStClk) {
			std::cout << "en move" << std::endl;
			for (int i = 0; i < thePath.size(); i++)
			{
				mTarget = thePath[i];
				GoTo(deltaTime);
			}
			mStateAction = eStateActionE::astar;
			bStClk = false;
			break;
		}
		break;
	default:
		break;
	}
	GoTo(deltaTime); 
}

void Enemigo::Render()
{
	int frameWidth = mTexture.width;
	int frameHeight = mTexture.height;
	
	Vector2 rnrPos = Grid::GetRealCoords(mPosition.x, mPosition.y);
	DrawTexture(mTexture, rnrPos.x, rnrPos.y, WHITE);
}

void Enemigo::End()
{
	UnloadTexture(mTexture);
}

sMoveResultE Enemigo::GoTo(float deltaTime)
{
	mTime += deltaTime;

	float epsilon = 10.f;
	VectorInt2 thrPos = GetEnemyPosition();
	VectorInt2 rtarget{ mTarget.x, mTarget.y };

	float cobaX = abs(thrPos.x - rtarget.x);
	float cobaY = abs(thrPos.y - rtarget.y);
	if (cobaX < epsilon && cobaY < epsilon) {
		// Set pos/orient to reset
		return sMoveResultE::arrived;
	}

	if (checkForBarriers(thrPos)) {
		return sMoveResultE::stoped;
	}

	int gox = 1;
	int goy = 1;
	Translate(gox, goy);

	return sMoveResultE::gook;
}

void Enemigo::SetTarget(int x, int y)
{
	mTime = 0.f;
	mTarget = VectorInt2{ x,y };

}

void Enemigo::SetPosition(int x, int y)
{
	mPosition = VectorInt2{ x,y };
}

void Enemigo::SetBarriers(const std::vector<Barrera> &barreras)
{
	mBarriers = barreras;
}

void Enemigo::SetOrbs(std::vector<VectorInt2>& orbsPos)
{
	orbs = orbsPos;
}

VectorInt2 Enemigo::GetEnemyPosition()
{
	return mPosition;
}

void Enemigo::Translate(int dx, int dy)
{
	mPosition =
	{ mPosition.x + dx, mPosition.y + dy };
}

bool Enemigo::checkForBarriers(const VectorInt2& pos)
{
	const VectorInt2& gridp = pos;
	sCell info[9] = {
		Grid::GetCell(gridp.x, gridp.y + 1),
		Grid::GetCell(gridp.x, gridp.y),
		Grid::GetCell(gridp.x, gridp.y - 1),
		Grid::GetCell(gridp.x - 1, gridp.y + 1),
		Grid::GetCell(gridp.x - 1, gridp.y),
		Grid::GetCell(gridp.x - 1, gridp.y - 1),
		Grid::GetCell(gridp.x + 1, gridp.y + 1),
		Grid::GetCell(gridp.x + 1, gridp.y),
		Grid::GetCell(gridp.x + 1, gridp.y - 1)
	};

	for (int cel = 0; cel < 9; cel++) {
		if (info[cel].object == eObjType::barrier) {
			return true;
		}
	}
	return false;
}


