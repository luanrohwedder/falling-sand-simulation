#include "water.h"

void WaterBehavior(Particle **grid, int x, int y)
{
    if (y + 1 >= ROWS)
        return;

    if (IsEmpty(grid, x, y + 1))
    {
        SwapParticle(grid, x, y, x, y + 1);
        return;
    }

    bool canDiagonalRight = false;
    bool canDiagonalLeft = false;

    if (IsEmpty(grid, x + 1, y + 1) && IsEmpty(grid, x + 1, y))
        canDiagonalRight = true;
    if (IsEmpty(grid, x - 1, y + 1) && IsEmpty(grid, x - 1, y))
        canDiagonalLeft = true;

    if (canDiagonalRight && canDiagonalLeft)
    {
        int dir = GetRandomValue(0, 1) == 0 ? -1 : 1;
        SwapParticle(grid, x, y, x + dir, y + 1);
        return;
    }
    else if (canDiagonalRight)
    {
        SwapParticle(grid, x, y, x + 1, y + 1);
        return;
    }
    else if (canDiagonalLeft)
    {
        SwapParticle(grid, x, y, x - 1, y + 1);
        return;
    }

    bool canRight = false;
    bool canLeft = false;

    if (IsEmpty(grid, x + 1, y))
        canRight = true;
    if (IsEmpty(grid, x - 1, y))
        canLeft = true;

    if (canRight && canLeft)
    {
        int dir = GetRandomValue(0, 1) == 0 ? -1 : 1;
        SwapParticle(grid, x, y, x + dir, y);
        return;
    }
    else if (canRight)
    {
        SwapParticle(grid, x, y, x + 1, y);
        return;
    }
    else if (canLeft)
    {
        SwapParticle(grid, x, y, x - 1, y);
        return;
    }
}

void CreateWater(Particle **grid, int x, int y, int brushSize)
{
    Color color[2] = {DARKBLUE, BLUE};

    for (int i = 0; i < brushSize && y + i < ROWS; i++)
    {
        for (int j = 0; j < brushSize && x + j < COLS; j++)
        {
            int rand = GetRandomValue(0, 1);
            if (IsEmpty(grid, x + j, y + i))
                grid[y + i][x + j] = (Particle){.type = WATER,
                                                .color = color[rand],
                                                .behavior = WaterBehavior};
        }
    }
}
