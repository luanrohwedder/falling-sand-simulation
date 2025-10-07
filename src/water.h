#ifndef WATER_H
#define WATER_H

#include "particle.h"

void WaterBehavior(Particle **grid, int x, int y);
void CreateWater(Particle **grid, int x, int y, int brushSize);

#endif // !WATER_H
