//#include "../raylib/raylib.h"
#include "../entorno/Grid.h"
#include "../agente/Agente.h"
#include "../enemigo/Enemigo.h"
#include "../orbes/OrbManager.h"
#include "../entorno/EntornoMgr.h"
#include <iostream>

enum class ePlayerTurno
{
	none = 0,
	agente,
	enemigo
};

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 800;

	ePlayerTurno pstate = ePlayerTurno::none;

	InitWindow(screenWidth, screenHeight, "juego del agente y enemigo");

	Grid::Initialize(screenWidth, screenHeight);

	Agente ahemte;
	Enemigo bigboss;
	OrbManager orbeMgr;

	ahemte.Initialize(screenWidth, screenHeight);
	bigboss.Initialize(screenWidth, screenHeight);

	EntornoMgr entomgr;
	entomgr.Initialize(screenWidth, screenHeight);
	entomgr.AddBorder();
	auto mpos = entomgr.AddEscena01();
	ahemte.SetPosition(mpos[0].x, mpos[0].y);
	bigboss.SetPosition(mpos[1].x, mpos[1].y);
	bigboss.SetTarget(ahemte.GetAgentPosition().x, ahemte.GetAgentPosition().y);

	orbeMgr.Initialize();
	bigboss.SetOrbs(orbeMgr.GetOrbesPos());
	//ahemte.SetTarget(60, 40);

	float accTime = 1.f;
	
	while (!WindowShouldClose()) 
	{
		float elapsedTime = GetFrameTime();
		accTime += elapsedTime;

		switch (pstate)
		{
		case ePlayerTurno::none:
			pstate = ePlayerTurno::agente;
			ahemte.StateClick();
			accTime = 0.8f;
			break;
		case ePlayerTurno::agente:
			ahemte.Update(elapsedTime);
			if(accTime > 1.0f) {
				ahemte.StateClick();
				pstate = ePlayerTurno::enemigo;
				accTime = 0.8f;
			}
			break;
		case ePlayerTurno::enemigo:
			bigboss.Update(elapsedTime, ahemte.GetAgentPosition());
			if (accTime > 1.0f) {
				bigboss.StateClick();
				pstate = ePlayerTurno::agente;
				accTime = 0.f;
			}
			break;
		default:
			break;
		}
		// Update
		//ahemte.Update(elapsedTime);

		// Draw		
		BeginDrawing();
		
		ClearBackground(RAYWHITE);

		for (size_t gap = 0; gap < 800; gap+=10) {
			DrawLine(gap, 0, gap, 800, LIGHTGRAY);
			DrawLine(0, gap, 800, gap, LIGHTGRAY);
		}

		entomgr.Render();
		ahemte.Render();
		bigboss.Render();

		orbeMgr.Render();
		
		EndDrawing();
		
	}
	ahemte.End();
	entomgr.End();
	CloseWindow();          
	
	return 0;
}