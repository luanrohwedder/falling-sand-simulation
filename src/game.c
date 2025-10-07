#include "particle.h"
#include "sand.h"
#include "stone.h"
#include "water.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

#define WIDTH 1280
#define HEIGHT 720

void Update(void);
void Draw(void);
Particle **CreateGrid(void);
void ResetGrid(void);

int brushSize = 3;
int selectedParticle = STONE;
bool reset = false;
Particle **grid;

int main(void)
{
    // -37 because hyprland bug
    InitWindow(WIDTH, HEIGHT - 37, "Testing");
    SetTargetFPS(60);

    grid = CreateGrid();

    while (!WindowShouldClose())
    {
        Update();

        BeginDrawing();

        Draw();

        EndDrawing();
    }

    CloseWindow();

    for (int y = 0; y < ROWS; y++)
        free(grid[y]);
    free(grid);

    return 0;
}

void Update(void)
{
    // RESET
    if (IsKeyPressed(KEY_R))
        ResetGrid();

    // SELECT TYPE
    if (IsKeyPressed(KEY_ONE))
        selectedParticle = SAND;
    if (IsKeyPressed(KEY_TWO))
        selectedParticle = WATER;
    if (IsKeyPressed(KEY_THREE))
        selectedParticle = STONE;

    // BRUSH SIZE
    brushSize += (int)GetMouseWheelMove();
    if (brushSize < 1)
        brushSize = 1;
    if (brushSize > 5)
        brushSize = 5;

    // PLACE PARTICLE
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        int x = (int)GetMousePosition().x / CELL_SIZE;
        int y = (int)GetMousePosition().y / CELL_SIZE;

        if (isEmpty(grid, x, y))
        {
            if (selectedParticle == SAND)
                CreateSand(grid, x, y, brushSize);
            if (selectedParticle == WATER)
                CreateWater(grid, x, y, brushSize);
            if (selectedParticle == STONE)
                CreateStone(grid, x, y, brushSize);
        }
    }

    UpdateParticle(grid);
}

void Draw(void)
{
    ClearBackground(BLACK);

    DrawText(TextFormat("Selected: %s", getParticleString(selectedParticle)),
             30, 20, 20, RAYWHITE);
    DrawText("1 - SAND", 30, 45, 18, YELLOW);
    DrawText("2 - WATER", 30, 70, 18, BLUE);
    DrawText("3 - STONE", 30, 95, 18, LIGHTGRAY);

    DrawText("R - RESET", 1100, 20, 20, RAYWHITE);
    DrawText(TextFormat("BRUSH SIZE: %d", brushSize), 1100, 50, 20, RAYWHITE);

    DrawParticle(grid);
}

Particle **CreateGrid(void)
{
    Particle **grid = malloc(ROWS * sizeof(Particle *));

    for (int y = 0; y < ROWS; y++)
    {
        grid[y] = malloc(COLS * sizeof(Particle));

        for (int x = 0; x < COLS; x++)
            grid[y][x] = (Particle){.type = 0};
    }

    return grid;
}

void ResetGrid(void)
{
    for (int y = 0; y < ROWS; y++)
        free(grid[y]);
    free(grid);

    grid = CreateGrid();
}
