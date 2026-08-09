#include "../headers/menu.h"
#include "../headers/utility.h"
#include "../headers/player.h"

int main()
{
    int index = 0, index2 = 1;

    InitWindow(GetScreenWidth(), 720, "Careoke");
    ToggleBorderlessWindowed();
    InitAudioDevice();
    tmp_tRay = LoadImage("utils/images/raylib.png");
    tmp_tLibtinyfiledialogs = LoadImage("utils/images/libtinyfiledialogs.png");
    tmp_tColorhunt = LoadImage("utils/images/colorhunt.png");
    tmp_tJ1gggs = LoadImage("utils/images/j1gggs.png");
    Music bg = LoadMusicStream("utils/audio/bg-from-yt.mp3");

    PlayMusicStream(bg);
    while (1)
    {
        if (mode == NOT)
            UpdateMusicStream(bg);
        else
            PauseMusicStream(bg);
        BeginDrawing();
        ClearBackground(Mencol);

        int menuState = DrawPlayMenu();

        if (menuState == 2)
        {
            PauseMusicStream(bg);

            if (!IsFileExtension(filePaths[index], ".mp3"))
            {
                index = 1;
                index2 = 0;
            }

            if (filePaths[index] != NULL && filePaths[index2] != NULL)
            {
                if (Player(filePaths[index], filePaths[index2]))
                {
                    menuState = 0;
                    for (int i = 0; i < MAX_FILEPATH_RECORDED; i++)
                    {
                        if (filePaths[i] != NULL)
                        {
                            RL_FREE(filePaths[i]);
                            filePaths[i] = NULL;
                        }
                    }
                    filePathCounter = 0;
                    SeekMusicStream(bg, 0.0f);
                    ResumeMusicStream(bg);
                }
            }
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