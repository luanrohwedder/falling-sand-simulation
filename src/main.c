#include "fire.h"
#include "particle.h"
#include "sand.h"
#include "stone.h"
#include "ui/button.h"
#include "water.h"
#include "wood.h"

#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

#define WIDTH 1280
#define HEIGHT 720

void Update(void);
void Draw(void);
Particle **CreateGrid(void);
void ResetGrid(void);
void CreateButtons(void);

int brushSize = 3;
int selectedParticle = STONE;
bool reset = false;
Particle **grid;
Button buttons[5];

int main(void)
{
    // -37 because hyprland bug
    InitWindow(WIDTH, HEIGHT - 37, "Testing");
    SetTargetFPS(60);

    grid = CreateGrid();
    CreateButtons();

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
    if (IsButtonPressed(buttons[0]) || IsKeyPressed(KEY_ONE))
        selectedParticle = SAND;
    if (IsButtonPressed(buttons[1]) || IsKeyPressed(KEY_TWO))
        selectedParticle = WATER;
    if (IsButtonPressed(buttons[2]) || IsKeyPressed(KEY_THREE))
        selectedParticle = STONE;
    if (IsButtonPressed(buttons[3]) || IsKeyPressed(KEY_FOUR))
        selectedParticle = WOOD;
    if (IsButtonPressed(buttons[4]) || IsKeyPressed(KEY_FIVE))
        selectedParticle = FIRE;

    // BRUSH SIZE
    brushSize += (int)GetMouseWheelMove();
    if (brushSize < 1)
        brushSize = 1;
    if (brushSize > 5)
        brushSize = 5;

    // PLACE PARTICLE
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) &&
        (!IsMouseOverButton(buttons[0]) && !IsMouseOverButton(buttons[1]) &&
         !IsMouseOverButton(buttons[2])))
    {
        int x = (int)GetMousePosition().x / CELL_SIZE;
        int y = (int)GetMousePosition().y / CELL_SIZE;

        if (IsEmpty(grid, x, y))
        {
            if (selectedParticle == SAND)
                CreateSand(grid, x, y, brushSize);
            if (selectedParticle == WATER)
                CreateWater(grid, x, y, brushSize);
            if (selectedParticle == STONE)
                CreateStone(grid, x, y, brushSize);
            if (selectedParticle == WOOD)
                CreateWood(grid, x, y, brushSize);
            if (selectedParticle == FIRE)
                CreateFire(grid, x, y, brushSize);
        }
    }

    UpdateParticle(grid);
}

void Draw(void)
{
    ClearBackground(BLACK);

    DrawParticle(grid);

    DrawText(TextFormat("Selected: %s", GetParticleString(selectedParticle)),
             30, 20, 20, RAYWHITE);

    for (int i = 0; i < 5; i++)
    {
        DrawRectangleRec(buttons[i].rect, buttons[i].color);
        DrawRectangleLinesEx(buttons[i].rect, 1, RAYWHITE);
        if (IsMouseOverButton(buttons[i]))
            DrawText(buttons[i].text, buttons[i].rect.x, buttons[i].rect.y + 30,
                     15, RAYWHITE);
    }

    DrawText("R - RESET", 1100, 20, 20, RAYWHITE);
    DrawText(TextFormat("BRUSH SIZE: %d", brushSize), 1100, 50, 20, RAYWHITE);
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

void CreateButtons()
{
    buttons[0] =
        CreateButton((Rectangle){.x = 250, .y = 20, .height = 20, .width = 20},
                     YELLOW, "SAND");
    buttons[1] =
        CreateButton((Rectangle){.x = 280, .y = 20, .height = 20, .width = 20},
                     BLUE, "WATER");
    buttons[2] =
        CreateButton((Rectangle){.x = 310, .y = 20, .height = 20, .width = 20},
                     LIGHTGRAY, "STONE");
    buttons[3] =
        CreateButton((Rectangle){.x = 340, .y = 20, .height = 20, .width = 20},
                     BROWN, "WOOD");
    buttons[4] = CreateButton(
        (Rectangle){.x = 370, .y = 20, .height = 20, .width = 20}, RED, "FIRE");
}
