#include <raylib.h>

int main(void)
{
    InitWindow(800, 480, "raylib");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Hello, World", GetScreenWidth() / 2, GetScreenHeight() / 2, 50, BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}