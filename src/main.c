#include "../headers/menu.h"
#include "../headers/utility.h"
#include "../headers/player.h"

int main()
{
    int index = 0, index2 = 1;

    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Careoke");
    InitAudioDevice();
    Music bg = LoadMusicStream("utils/audio/bg-from-yt.mp3");

    PlayMusicStream(bg);
    while (!WindowShouldClose())
    {
        if (mode != PLAYING)
            UpdateMusicStream(bg);
        else
        {
            if (bg.stream.buffer != NULL)
            {
                StopMusicStream(bg);
                UnloadMusicStream(bg);
                bg.stream.buffer = NULL;
            }
        }
        BeginDrawing();
        ClearBackground(Mencol);

        int menuState = DrawPlayMenu();

        if (menuState == 2)
        {
            if (!IsFileExtension(filePaths[index], ".mp3"))
            {
                index = 1;
                index2 = 0;
            }

            if (filePaths[index] != NULL && filePaths[index2] != NULL)
                if (Player(filePaths[index], filePaths[index2]))
                    break;
        }
        if (menuState == 1)
        {
            break;
        }

        EndDrawing();
    }
    UnloadMusicStream(bg);
    UnloadTimages();

    for (int i = 0; i < MAX_FILEPATH_RECORDED; i++)
    {
        if (filePaths[i] != NULL)
        {
            RL_FREE(filePaths[i]);
            filePaths[i] = NULL;
        }
    }
    CloseWindow();

    return 0;
}