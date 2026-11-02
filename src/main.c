#include "../headers/menu.h"
#include "../headers/utility.h"
#include "../headers/player.h"
#include "../headers/parser.h"
#ifndef DEBUG
#include "../headers/binSource.h"
#endif // !DEBUG

int main()
{
    Deck cards = {0};
    Settings sett = {0};
    char *AppData = nullptr;

#ifdef _WIN32
    char *appDir = getenv("APPDATA");
#else
    char *appDir = nullptr;
    char *TmpappDir = getenv("HOME");
    size_t tmpappdir_sz = snprintf(NULL, 0, "%s/.local/share/", TmpappDir);
    appDir = malloc(tmpappdir_sz + 1);
    snprintf(appDir, tmpappdir_sz + 1, "%s/.local/share/", TmpappDir);
#endif // DEBUG

    size_t AD_sz = snprintf(NULL, 0, "%s/Careoke/config/default.liboke", appDir);
    AppData = malloc(AD_sz + 1);
    snprintf(AppData, AD_sz + 1, "%s/Careoke/config/default.liboke", appDir);

    if (!FileExists(AppData))
    {
        if (!FileExists(TextFormat("%s/Careoke", appDir)))
            MakeDirectory(TextFormat("%s/Careoke", appDir));
        if (!FileExists(TextFormat("%s/Careoke/config", appDir)))
            MakeDirectory(TextFormat("%s/Careoke/config", appDir));
        ResetLiboke(AppData);
    }
    else
    {
        if (ValidateOke(AppData))
        {
            TraceLog(LOG_ERROR, "CAREOKE: MAIN: INVALID LIBOKE FILE");
            return 1;
        }

        ReadOKEData(AppData, &cards, &sett);
    }

    int index = 0, index2 = 1;

    InitWindow(GetScreenWidth(), 720, "Careoke");
    ToggleBorderlessWindowed();
    InitAudioDevice();
#ifdef DEBUG
    tmp_tRay = LoadImage("utils/images/logo_raylib.png");
    tmp_tLibtinyfiledialogs = LoadImage("utils/images/libtinyfiledialogs.png");
    tmp_tColorhunt = LoadImage("utils/images/colorhunt.png");
    tmp_tJ1gggs = LoadImage("utils/images/j1gggs.png");
    Music bg = LoadMusicStream("utils/audio/bg-from-yt.mp3");
#else
    tmp_tRay = LoadImageFromMemory(".png", logo_raylib, logo_raylib_size);
    tmp_tLibtinyfiledialogs = LoadImageFromMemory(".png", libtinyfiledialogs, libtinyfiledialogs_size);
    tmp_tColorhunt = LoadImageFromMemory(".png", colorhunt, colorhunt_size);
    tmp_tJ1gggs = LoadImageFromMemory(".png", j1gggs, j1gggs_size);
    Music bg = LoadMusicStreamFromMemory(".mp3", bg_from_yt, bg_from_yt_size);
#endif

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
    free(AppData);
#ifdef __linux__
    free(appDir);
#endif
    freeFilePaths();
    CloseWindow();

    return 0;
}