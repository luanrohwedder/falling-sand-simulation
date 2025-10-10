#ifndef WOOD_H
#define WOOD_H

#include "particle.h"

void WoodBehavior(Particle **grid, int x, int y);

void CreateWood(Particle **grid, int x, int y, int brushSize);

#endif // !WOOD_H
