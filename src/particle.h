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
} Particles;

typedef struct Particle Particle;

struct Particle
{
    int type;
    Color color;
    int lastDir;
    void (*behavior)(Particle **grid, int x, int y);
};

/*
 * Util Methods
 */
bool isEmpty(Particle **grid, int x, int y);
bool verifyDown(Particle **grid, int x, int y, int type);
bool verifyDiagonal(Particle **grid, int x, int y, int type, int direction);
bool verifySide(Particle **grid, int x, int y, int type, int direction);
void swapParticle(Particle **grid, int x1, int y1, int x2, int y2);
char *getParticleString(int type);

/*
 * Core Methods
 */
void UpdateParticle(Particle **grid);
void DrawParticle(Particle **grid);

#endif // PARTICLE_H
