#include <raylib.h>
#include "../headers/tokenizer.h"

int main(void)
{
    InitWindow(1920, 1080, "raylib");
    InitAudioDevice();

    Token tokens[MAX_LINES];
    int count = GetLRC("out/lyrics.lrc", tokens);
    int ti = 0;

    SetTargetFPS(60);

    Music mus = LoadMusicStream("out/music.mp3");
    float curTime = 0.0f;
    PlayMusicStream(mus);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(mus);
        curTime = GetMusicTimePlayed(mus);
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (ti < count - 1 && curTime >= tokens[ti + 1].time)
            ti++;

        if (ti > 0)
            DrawText(TextFormat("%s", tokens[ti - 1].lyric), (GetScreenWidth() / 2) - ((MeasureText(tokens[ti - 1].lyric, 25)) / 2), (GetScreenHeight() / 2) - 100, 25, BLACK);
        DrawText(TextFormat("%s", tokens[ti].lyric), (GetScreenWidth() / 2) - ((MeasureText(tokens[ti].lyric, 50)) / 2), GetScreenHeight() / 2, 50, BLACK);
        if (ti < count - 1)
            DrawText(TextFormat("%s", tokens[ti + 1].lyric), (GetScreenWidth() / 2) - ((MeasureText(tokens[ti + 1].lyric, 25)) / 2), (GetScreenHeight() / 2) + 100, 25, BLACK);

        EndDrawing();
    }
    CloseAudioDevice();
    CloseWindow();

    return 0;
}