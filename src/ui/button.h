#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>
#include <stdbool.h>

typedef struct
{
    Rectangle rect;
    Color color;
    char *text;
} Button;

Button CreateButton(Rectangle rect, Color color, char *text);

bool IsMouseOverButton(Button button);

bool IsButtonPressed(Button button);

#endif // !BUTTON_H
