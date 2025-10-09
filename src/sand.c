#include "sand.h"

void SandBehavior(Particle **grid, int x, int y)
{
    if (y + 1 >= ROWS)
        return;

    // DOWN
    if (IsEmpty(grid, x, y + 1) || IsParticle(grid, x, y + 1, WATER))
    {
        SwapParticle(grid, x, y, x, y + 1);
    }
    else if (!IsParticle(grid, x, y + 1, STONE))
    {
        int dir = 0;
        bool canRight = false;
        bool canLeft = false;

        // RIGHT
        if (IsEmpty(grid, x + 1, y + 1) ||
            IsParticle(grid, x + 1, y + 1, WATER))
            canRight = true;
        // LEFT
        if (IsEmpty(grid, x - 1, y + 1) ||
            IsParticle(grid, x - 1, y + 1, WATER))
            canLeft = true;

        if (canRight && canLeft)
            dir = GetRandomValue(0, 1) == 0 ? -1 : 1;
        else if (canRight)
            dir = 1;
        else if (canLeft)
            dir = -1;

        if (dir != 0)
            SwapParticle(grid, x, y, x + dir, y + 1);
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
            if (IsEmpty(grid, x + j, y + i))
                grid[y + i][x + j] = (Particle){.type = SAND,
                                                .color = color[rand],
                                                .behavior = SandBehavior};
        }
    }
}
