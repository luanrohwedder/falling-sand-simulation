#include "sand.h"

void SandBehavior(Particle **grid, int x, int y)
{
    if (y + 1 >= ROWS)
        return;

    // DOWN
    if (verifyDown(grid, x, y, EMPTY) || verifyDown(grid, x, y, WATER))
    {
        swapParticle(grid, x, y, x, y + 1);
    }
    else if (grid[y + 1][x].type != STONE)
    {
        int dir = 0;
        bool canRight = false;
        bool canLeft = false;

        // RIGHT
        if (verifyDiagonal(grid, x, y, EMPTY, 1) ||
            verifyDiagonal(grid, x, y, WATER, 1))
            canRight = true;
        // LEFT
        if (verifyDiagonal(grid, x, y, EMPTY, -1) ||
            verifyDiagonal(grid, x, y, WATER, -1))
            canLeft = true;

        if (canRight && canLeft)
            dir = GetRandomValue(0, 1) == 0 ? -1 : 1;
        else if (canRight)
            dir = 1;
        else if (canLeft)
            dir = -1;

        if (dir != 0)
            swapParticle(grid, x, y, x + dir, y + 1);
    }
}

void CreateSand(Particle **grid, int x, int y, int brushSize)
{
    Color color[3] = {ORANGE, GOLD, YELLOW};

    for (int i = 0; i < brushSize && y + i < ROWS; i++)
    {
        for (int j = 0; j < brushSize && x + j < COLS; j++)
        {
            int rand = GetRandomValue(0, 2);
            grid[y + i][x + j] = (Particle){
                .type = SAND, .color = color[rand], .behavior = SandBehavior};
        }
    }
}
