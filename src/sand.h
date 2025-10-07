#ifndef SAND_H
#define SAND_H

#include "particle.h"

void SandBehavior(Particle **grid, int x, int y);
void CreateSand(Particle **grid, int x, int y, int brushSize);

#endif // !SAND_H
