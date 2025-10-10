#include "wood.h"

void WoodBehavior(Particle **grid, int x, int y) {}

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
