#include "../headers/menu.h"
#include "../headers/utility.h"

Rectangle play = {0, 0, 400, 75};
Rectangle setting = {0, 0, 400, 75};
Rectangle credit = {0, 0, 400, 75};
Rectangle close = {0, 0, 50, 50};

enum OPT option = NONE;

bool isWindowFocus = false;

void idk()
{
    // i don't know
}

void DrawPlay()
{
}

enum OPT DrawSett()
{
    close.x = (GetScreenWidth() - GetScreenWidth() * 0.15f) + 50;
    close.y = (((GetScreenHeight() / 2) - (GetScreenHeight() - GetScreenHeight() * 0.15f) / 2)) + 50;

    DrawRectangle(
        (((GetScreenWidth() / 2) - (GetScreenWidth() - GetScreenWidth() * 0.15f) / 2)),
        (((GetScreenHeight() / 2) - (GetScreenHeight() - GetScreenHeight() * 0.15f) / 2)),
        (GetScreenWidth() - GetScreenWidth() * 0.15f),
        (GetScreenHeight() - GetScreenHeight() * 0.15f),
        (Color){100, 100, 100, 200});

    DrawText("X", (GetScreenWidth() - GetScreenWidth() * 0.15f) + 50, (((GetScreenHeight() / 2) - (GetScreenHeight() - GetScreenHeight() * 0.15f) / 2)) + 50, 50, BLACK);
    DrawRectangleRec(close, (Color){0, 0, 0, 0});
    if (hoverButton(close) && (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
        return NONE;
    return SETTINGS;
}

enum OPT DrawCre()
{
    close.x = (GetScreenWidth() - GetScreenWidth() * 0.15f) + 50;
    close.y = (((GetScreenHeight() / 2) - (GetScreenHeight() - GetScreenHeight() * 0.15f) / 2)) + 50;

    DrawRectangle(
        (((GetScreenWidth() / 2) - (GetScreenWidth() - GetScreenWidth() * 0.15f) / 2)),
        (((GetScreenHeight() / 2) - (GetScreenHeight() - GetScreenHeight() * 0.15f) / 2)),
        (GetScreenWidth() - GetScreenWidth() * 0.15f),
        (GetScreenHeight() - GetScreenHeight() * 0.15f),
        (Color){100, 100, 100, 200});

    DrawText("X", (GetScreenWidth() - GetScreenWidth() * 0.15f) + 50, (((GetScreenHeight() / 2) - (GetScreenHeight() - GetScreenHeight() * 0.15f) / 2)) + 50, 50, BLACK);
    DrawRectangleRec(close, (Color){0, 0, 0, 0});
    if (hoverButton(close) && (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
        return NONE;
    return CREDIT;
}

void DrawPlayMenu()
{
    if (option != NONE)
        isWindowFocus = true;
    else
        isWindowFocus = false;

    DrawText("C", ((GetScreenWidth() / 2) - (MeasureText("Careoke", 120) / 2)) + 120, (((GetScreenHeight() / 2) - 125)), 120, Ccol);
    DrawText("areoke", ((GetScreenWidth() / 2) - (MeasureText("areoke", 50) / 2)), (GetScreenHeight() / 2) - 100, 50, Tcol);
    DrawRectangle(((GetScreenWidth() / 2) - (MeasureText("areoke", 50) / 2)) + 40, (GetScreenHeight() / 2) - 50, 200, 25, Bocol);

    play.x = ((GetScreenWidth() / 2) - (MeasureText("Careoke", 50) / 2)) - 75;
    play.y = (GetScreenHeight() / 2) + 40;
    DrawRectangleRec(play, Butcol1);
    setting.x = play.x;
    setting.y = (GetScreenHeight() / 2) + (40 + 75 + 15);
    DrawRectangleRec(setting, Butcol2);
    credit.x = play.x;
    credit.y = (GetScreenHeight() / 2) + (40 + 75 + 106);
    DrawRectangleRec(credit, Butcol3);

    DrawText("PLAY", play.x + ((play.width / 2) - MeasureText("PLAY", 50) / 2), play.y + 15, 50, Textcol);
    DrawText("SETTINGS", setting.x + ((setting.width / 2) - MeasureText("SETTINGS", 50) / 2), setting.y + 15, 50, Textcol);
    DrawText("CREDITS", credit.x + ((credit.width / 2) - MeasureText("CREDITS", 50) / 2), credit.y + 15, 50, Textcol);

    if (!isWindowFocus)
    {
        if (hoverButton(play))
            Butcol1.a = 150;
        else
            Butcol1.a = 255;

        if (hoverButton(setting))
            Butcol2.a = 150;
        else
            Butcol2.a = 255;

        if (hoverButton(credit))
            Butcol3.a = 150;
        else
            Butcol3.a = 255;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (hoverButton(play))
            option = PLAY;
        if (hoverButton(setting))
            option = SETTINGS;
        if (hoverButton(credit))
            option = CREDIT;
    }

    if (option == PLAY)
        DrawPlay();
    else if (option == SETTINGS)
        option = DrawSett();
    else if (option == CREDIT)
        option = DrawCre();
    else
        idk();
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