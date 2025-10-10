#include "particle.h"
#include <stdbool.h>

bool IsEmpty(Particle **grid, int x, int y)
{
    if (x < 0 || x >= COLS || y < 0 || y >= ROWS)
        return false;
    return grid[y][x].type == EMPTY;
}

bool IsParticle(Particle **grid, int x, int y, Particles particle)
{
    if (x < 0 || x >= COLS || y < 0 || y >= ROWS)
        return false;
    return grid[y][x].type == particle;
}

void SwapParticle(Particle **grid, int orgX, int orgY, int destX, int destY)
{
    Particle temp = grid[orgY][orgX];
    grid[orgY][orgX] = grid[destY][destX];
    grid[destY][destX] = temp;
}

char *GetParticleString(int type)
{
    if (type == SAND)
        return "SAND";
    if (type == WATER)
        return "WATER";
    if (type == STONE)
        return "STONE";
    if (type == WOOD)
        return "WOOD";
    if (type == FIRE)
        return "FIRE";

    return "";
}

void UpdateParticle(Particle **grid)
{
    for (int y = ROWS - 1; y >= 0; y--)
    {
        for (int x = 0; x < COLS; x++)
        {
            if (grid[y][x].behavior && grid[y][x].type != FIRE)
                grid[y][x].behavior(grid, x, y);
        }
    }

    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            if (grid[y][x].type == FIRE)
                grid[y][x].behavior(grid, x, y);
        }
    }
}

void DrawParticle(Particle **grid)
{
    for (int y = ROWS - 1; y >= 0; y--)
    {
        for (int x = 0; x < COLS; x++)
        {
            if (grid[y][x].type == EMPTY)
                continue;

            DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE,
                          grid[y][x].color);
        }
    }
}
