#include "../headers/menu.h"
#include "../headers/utility.h"

int main()
{
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "test");
    InitAudioDevice();
    Music bg = LoadMusicStream("utils/audio/bg-from-yt.mp3");

    PlayMusicStream(bg);
    while (!WindowShouldClose())
    {
        if (mode == START)
            UpdateMusicStream(bg);
        else
            UnloadMusicStream(bg);
        BeginDrawing();
        ClearBackground(Mencol);

        DrawPlayMenu();

        if (DrawPlayMenu())
        {
            EndDrawing();
            UnloadMusicStream(bg);
            CloseWindow();
            return 0;
        }

        EndDrawing();
    }
    UnloadMusicStream(bg);
    CloseWindow();

    return 0;
}