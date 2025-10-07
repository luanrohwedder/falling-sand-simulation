#include "particle.h"
#include <stdbool.h>

bool isEmpty(Particle **grid, int x, int y) { return grid[y][x].type == EMPTY; }

bool verifyDown(Particle **grid, int x, int y, int type)
{
    return grid[y + 1][x].type == type;
}

bool verifyDiagonal(Particle **grid, int x, int y, int type, int direction)
{
    int nx = x + direction;
    return nx < COLS && nx >= 0 && grid[y + 1][nx].type == type;
}

bool verifySide(Particle **grid, int x, int y, int type, int direction)
{
    int nx = x + direction;
    return nx < COLS && nx >= 0 && grid[y][nx].type == type;
}

void swapParticle(Particle **grid, int orgX, int orgY, int destX, int destY)
{
    Particle temp = grid[orgY][orgX];
    grid[orgY][orgX] = grid[destY][destX];
    grid[destY][destX] = temp;
}

char *getParticleString(int type)
{
    if (type == SAND)
        return "SAND";
    if (type == WATER)
        return "WATER";
    if (type == STONE)
        return "STONE";

    return "";
}

void UpdateParticle(Particle **grid)
{
    for (int y = ROWS - 1; y >= 0; y--)
    {
        for (int x = 0; x < COLS; x++)
        {
            if (grid[y][x].behavior)
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
