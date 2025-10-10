#ifndef PARTICLE_H
#define PARTICLE_H

#include "raylib.h"
#include <stdbool.h>

#define COLS 256
#define ROWS 144
#define CELL_SIZE 5

typedef enum
{
    EMPTY = 0,
    SAND = 1,
    WATER = 2,
    STONE = 3,
    WOOD = 4,
    FIRE = 5,
} Particles;

typedef struct Particle Particle;

struct Particle
{
    int type;
    Color color;
    float lifeTime;
    void (*behavior)(Particle **grid, int x, int y);
};

/*
 * Util Methods
 */
bool IsEmpty(Particle **grid, int x, int y);
bool IsParticle(Particle **grid, int x, int y, Particles particle);
void SwapParticle(Particle **grid, int x1, int y1, int x2, int y2);
char *GetParticleString(int type);

/*
 * Core Methods
 */
void UpdateParticle(Particle **grid);
void DrawParticle(Particle **grid);

#endif // PARTICLE_H
