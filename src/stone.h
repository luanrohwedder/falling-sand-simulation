#ifndef STONE_H
#define STONE_H

#include "particle.h"

void StoneBehavior(Particle **grid, int x, int y);

void CreateStone(Particle **grid, int x, int y, int brushSize);

#endif // !STONE_H
