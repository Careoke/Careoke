#include "../headers/menu.h"
#include "../headers/utility.h"

Rectangle play = {0, 0, 400, 75};
Rectangle setting = {0, 0, 400, 75};
Rectangle credit = {0, 0, 400, 75};

void DrawPlayMenu()
{
    DrawText("C", ((GetScreenWidth() / 2) - (MeasureText("Careoke", 120) / 2)) + 120, (((GetScreenHeight() / 2) - 125)), 120, Ccol);
    DrawText("areoke", ((GetScreenWidth() / 2) - (MeasureText("areoke", 50) / 2)), (GetScreenHeight() / 2) - 100, 50, Tcol);
    DrawRectangle(((GetScreenWidth() / 2) - (MeasureText("areoke", 50) / 2)) + 40, (GetScreenHeight() / 2) - 50, 200, 25, Bocol);

    play.x = ((GetScreenWidth() / 2) - (MeasureText("Careoke", 50) / 2)) - 75;
    play.y = (GetScreenHeight() / 2) + 40;
    DrawRectangleRec(play, Butcol);
    setting.x = play.x;
    setting.y = (GetScreenHeight() / 2) + (40 + 75 + 15);
    DrawRectangleRec(setting, Butcol);
    credit.x = play.x;
    credit.y = (GetScreenHeight() / 2) + (40 + 75 + 106);
    DrawRectangleRec(credit, Butcol);

    DrawText("PLAY", play.x + ((play.width / 2) - MeasureText("PLAY", 50) / 2), play.y + 15, 50, Textcol);
    DrawText("SETTINGS", setting.x + ((setting.width / 2) - MeasureText("SETTINGS", 50) / 2), setting.y + 15, 50, Textcol);
    DrawText("CREDITS", credit.x + ((credit.width / 2) - MeasureText("CREDITS", 50) / 2), credit.y + 15, 50, Textcol);
}

int main()
{
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "test");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Mencol);

        DrawPlayMenu();

        EndDrawing();
    }

    CloseWindow();
}