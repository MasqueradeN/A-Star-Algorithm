#include "Shooter.h"
#include "../raylib/raymath.h"
#include "../entorno/Grid.h"
#include <cmath>
#include <iostream>

sCell bresenham(int x0, int y0, int x1, int y1)
{
  int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = (dx > dy ? dx : -dy) / 2;

  while (x0 != x1 || y0 != y1) {
    sCell found = Grid::GetCell(x0, y0);
    if (found.object != eObjType::none) {
      found.fx = x0; found.fy = y0;
      return found;
    }
    //setpixel(x0, y0);
    int e2 = err;
    if (e2 > -dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
  return sCell{ eObjType::none, -1, -1 };
}

sCell Shooter::getRayHit(Vector2 p0, Vector2 dir)
{
  Vector2 pn = { p0.x + (100.f * dir.x), p0.y + (100.f * dir.y) };
  return bresenham(p0.x, p0.y, pn.x, pn.y);
}

std::vector<sCell> Shooter::getRayHitsPattern1(Vector2 p0, Vector2 dir)
{
  float ang = (mAngCvr * DEG2RAD) / mNumRays;
  float orgAng = atan2f(dir.y, dir.x);
  std::vector<sCell> retClVec;

  for (int i = 0; i < mNumRays; i++) {
    float idAng = orgAng + (((float)i - 5.f) * ang);
    sCell rcl = getRayHit(p0, { cosf(idAng), sinf(idAng) });
    if (rcl.object != eObjType::none) {
      retClVec.push_back(rcl);
    }
  }
  return retClVec;
}


