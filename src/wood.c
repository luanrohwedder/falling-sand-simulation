#include "wood.h"

void WoodBehavior(Particle **grid, int x, int y)
{
    if (grid[y][x].lifeTime > 0)
    {
        grid[y][x].lifeTime -= GetFrameTime();

        float t = grid[y][x].lifeTime;
        float r = GetRandomValue(0, 1000) / 1000.0f;
        if (r < 0.1f && (t > 0.9f && t < 1.3f))
        {
            int xDir = GetRandomValue(-1, 1);
            int yDir = GetRandomValue(-1, 1);
            int nx = x + xDir;
            int ny = y + yDir;

            if (IsParticle(grid, nx, ny, WOOD) && grid[ny][nx].lifeTime == 0)
                grid[ny][nx].lifeTime = 1.5f;
        }
    }

    if (grid[y][x].lifeTime < 0)
    {
        grid[y][x] = (Particle){0};
        return;
    }

    float t = grid[y][x].lifeTime;

    if (t > 1.0f)
        grid[y][x].color = BROWN;
    else if (t > 0.6f)
        grid[y][x].color = ORANGE;
    else if (t > 0.3f)
        grid[y][x].color = RED;
    else if (t > 0)
        grid[y][x].color = DARKGRAY;
}

void CreateWood(Particle **grid, int x, int y, int brushSize)
{
    Color color[2] = {DARKBROWN, BROWN};

    for (int i = 0; i < brushSize && y + i < ROWS; i++)
    {
        for (int j = 0; j < brushSize && x + j < COLS; j++)
        {
            int rand = GetRandomValue(0, 1);
            if (IsEmpty(grid, x + j, y + i))
                grid[y + i][x + j] = (Particle){.type = WOOD,
                                                .color = color[rand],
                                                .behavior = WoodBehavior};
        }
    }
}
