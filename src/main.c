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
                    index = 0;
                    index2 = 1;
                    menuState = 0;
                    freeFilePaths();
                    free(tmpMp3Path);
                    free(tmpLrcPath);
                    tmpMp3Path = NULL;
                    tmpLrcPath = NULL;
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
    freeFilePaths();
    CloseWindow();

    return 0;
}