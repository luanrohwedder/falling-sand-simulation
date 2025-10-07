#include "stone.h"

void StoneBehavior(Particle **grid, int x, int y) {}

void CreateStone(Particle **grid, int x, int y, int brushSize)
{
    Color color[3] = {GRAY, LIGHTGRAY};

    for (int i = 0; i < brushSize && y + i < ROWS; i++)
    {
        for (int j = 0; j < brushSize && x + j < COLS; j++)
        {
            int rand = GetRandomValue(0, 1);
            grid[y + i][x + j] = (Particle){
                .type = STONE, .color = color[rand], .behavior = StoneBehavior};
        }
    }
}
