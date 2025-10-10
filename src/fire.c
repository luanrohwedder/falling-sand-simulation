#include "fire.h"

void FireBehavior(Particle **grid, int x, int y)
{
    if (y < 0 || y >= ROWS)
        return;

    grid[y][x].lifeTime -= GetFrameTime();

    if (grid[y][x].lifeTime <= 0)
    {
        grid[y][x] = (Particle){0};
        return;
    }

    if (grid[y][x].lifeTime < 0.3f)
    {
        float r = GetRandomValue(0, 1000) / 1000.f;

        if (r < 0.7f)
            grid[y][x].color = GOLD;
        else if (r < 0.95f)
            grid[y][x].color = ORANGE;
        else
            grid[y][x].color = RED;
    }
    else if (grid[y][x].lifeTime < 0.6f)
    {
        float r = GetRandomValue(0, 1000) / 1000.f;

        if (r < 0.40)
            grid[y][x].color = GOLD;
        else if (r < 0.70)
            grid[y][x].color = ORANGE;
        else
            grid[y][x].color = RED;
    }
    else
    {
        float r = GetRandomValue(0, 1000) / 1000.f;

        if (r < 0.10)
            grid[y][x].color = GOLD;
        else if (r < 0.50)
            grid[y][x].color = ORANGE;
        else
            grid[y][x].color = RED;
    }

    float r = GetRandomValue(0, 1000) / 1000.f;
    int nx = x;
    int ny = y;

    if (r <= 0.6f)
        ny -= 1;
    else if (r < 0.75f)
    {
        ny -= 1;
        nx -= 1;
    }
    else if (r < 0.90)
    {
        ny -= 1;
        nx += 1;
    }
    else if (r < 0.95)
        nx -= 1;
    else
        nx += 1;

    if (IsEmpty(grid, nx, ny))
    {
        SwapParticle(grid, x, y, nx, ny);
        return;
    }

    if (IsParticle(grid, nx, ny, WOOD))
    {
        grid[ny][nx] = (Particle){0};
    }
}

void CreateFire(Particle **grid, int x, int y, int brushSize)
{
    Color color[2] = {RED, ORANGE};

    for (int i = 0; i < brushSize && y + i < ROWS; i++)
    {
        for (int j = 0; j < brushSize && x + j < COLS; j++)
        {
            int rand = GetRandomValue(0, 1);
            if (IsEmpty(grid, x + j, y + i))
                grid[y + i][x + j] = (Particle){
                    .type = FIRE,
                    .color = RED,
                    .lifeTime = 0.3f + (GetRandomValue(0, 1000) / 1000.f) *
                                           (0.8f - 0.3f),
                    .behavior = FireBehavior};
        }
    }
}
