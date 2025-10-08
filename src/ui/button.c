#include "button.h"

Button CreateButton(Rectangle rect, Color color, char *text)
{
    Button btn;
    btn.rect = rect;
    btn.color = color;
    btn.text = text;
    return btn;
}

bool IsMouseOverButton(Button button)
{
    return CheckCollisionPointRec(GetMousePosition(), button.rect);
}

bool IsButtonPressed(Button button)
{
    return CheckCollisionPointRec(GetMousePosition(), button.rect) &&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}
