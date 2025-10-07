#include "water.h"

void WaterBehavior(Particle **grid, int x, int y)
{
    if (y + 1 >= ROWS)
        return;

    if (verifyDown(grid, x, y, EMPTY))
    {
        swapParticle(grid, x, y, x, y + 1);
        return;
    }

    bool canDiagonalRight = false;
    bool canDiagonalLeft = false;

    if (verifyDiagonal(grid, x, y, EMPTY, 1) &&
        verifySide(grid, x, y, EMPTY, 1))
        canDiagonalRight = true;
    if (verifyDiagonal(grid, x, y, EMPTY, -1) &&
        verifySide(grid, x, y, EMPTY, -1))
        canDiagonalLeft = true;

    if (canDiagonalRight && canDiagonalLeft)
    {
        int dir = GetRandomValue(0, 1) == 0 ? -1 : 1;
        swapParticle(grid, x, y, x + dir, y + 1);
        return;
    }
    else if (canDiagonalRight)
    {
        swapParticle(grid, x, y, x + 1, y + 1);
        return;
    }
    else if (canDiagonalLeft)
    {
        swapParticle(grid, x, y, x - 1, y + 1);
        return;
    }

    if (grid[y][x].lastDir != 0)
    {
        int dir = grid[y][x].lastDir;
        int nx = x + dir;

        if (verifySide(grid, x, y, EMPTY, dir))
        {
            swapParticle(grid, x, y, nx, y);
            grid[y][nx].lastDir = dir;
            return;
        }
        else
        {
            dir *= -1;
            nx = x + dir;

            if (verifySide(grid, x, y, EMPTY, dir))
            {
                swapParticle(grid, x, y, nx, y);
                grid[y][nx].lastDir = dir;
                return;
            }
            else
            {
                grid[y][x].lastDir = 0;
                return;
            }
        }
    }

    bool canRight = false;
    bool canLeft = false;

    if (verifySide(grid, x, y, EMPTY, 1))
        canRight = true;
    if (verifySide(grid, x, y, EMPTY, -1))
        canLeft = true;

    if (canRight && canLeft)
    {
        int dir = GetRandomValue(0, 1) == 0 ? -1 : 1;
        swapParticle(grid, x, y, x + dir, y);
        grid[y][x + dir].lastDir = dir;
        return;
    }
    else if (canRight)
    {
        swapParticle(grid, x, y, x + 1, y);
        grid[y][x + 1].lastDir = 1;
        return;
    }
    else if (canLeft)
    {
        swapParticle(grid, x, y, x - 1, y);
        grid[y][x - 1].lastDir = -1;
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
            grid[y + i][x + j] = (Particle){
                .type = WATER, .color = color[rand], .behavior = WaterBehavior};
        }
    }
}
