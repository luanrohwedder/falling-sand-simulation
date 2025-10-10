#ifndef FIRE_H
#define FIRE_H

#include "particle.h"

void FireBehavior(Particle **grid, int x, int y);

void CreateFire(Particle **grid, int x, int y, int brushSize);

#endif // !FIRE_H
