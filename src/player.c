#include "../headers/player.h"

bool seal = 1;

bool Player(char *musicDir, char *lrcDir)
{
    static Music mus;
    static float curTime = 0.0f;
    static int ti = 0;
    static int count = 0;
    static Token tokens[MAX_LINES];
    static bool isLoaded = 0;

    if (seal == 1 && !isLoaded)
    {
        if (!IsAudioDeviceReady())
            InitAudioDevice();
        count = GetLRC(lrcDir, tokens);
        mus = LoadMusicStream(musicDir);

        PlayMusicStream(mus);
        seal = 0;
        isLoaded = 1;
    }

    if (isLoaded)
    {
        UpdateMusicStream(mus);
        curTime = GetMusicTimePlayed(mus);

        if (ti < count - 1 && curTime >= tokens[ti + 1].time)
            ti++;

        if (ti > 0)
            DrawText(
                TextFormat(
                    "%s",
                    tokens[ti - 1].lyric),
                (GetScreenWidth() / 2) - ((MeasureText(tokens[ti - 1].lyric, 25)) / 2),
                (GetScreenHeight() / 2) - 100,
                25, BLACK);

        DrawText(
            TextFormat(
                "%s",
                tokens[ti].lyric),
            (GetScreenWidth() / 2) - ((MeasureText(tokens[ti].lyric, 50)) / 2),
            GetScreenHeight() / 2,
            50, BLACK);

        if (ti < count - 1)
            DrawText(
                TextFormat(
                    "%s",
                    tokens[ti + 1].lyric),
                (GetScreenWidth() / 2) - ((MeasureText(tokens[ti + 1].lyric, 25)) / 2),
                (GetScreenHeight() / 2) + 100,
                25, BLACK);
    }

    if (GetMusicTimePlayed(mus) >= GetMusicTimeLength(mus) - 0.1f)
    {
        isLoaded = false;
        ti = 0;
        CloseAudioDevice();
        return true;
    }
    return false;
}