#include "../headers/player.h"

bool seal = 1;
Rectangle Play = {0, 0, 400, 75};
Rectangle Setting = {0, 0, 400, 75};
Rectangle pExit = {0, 0, 400, 75};
Rectangle Restart = {0, 0, 400, 75};
Rectangle PauseBound = {30, 30, 30 + 30 + 5, 60};

Color PbutCol1 = {136, 189, 164, 255};
Color PbutCol2 = {136, 189, 164, 255};
Color PbutCol3 = {136, 189, 164, 255};
Color PbutCol4 = {136, 189, 164, 255};

Color Texcol = {27, 60, 83, 255};
Color Tcolor = {230, 57, 70, 255};

bool Player(char *musicDir, char *lrcDir)
{
    if (filePathCounter != 2)
        filePathCounter = 2; // hardcoding it
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

    if (IsKeyPressed(KEY_ESCAPE))
    {
        if (mode == PLAYING)
        {
            mode = PAUSED;
            PauseMusicStream(mus);
        }
        else
        {
            mode = PLAYING;
            PlayMusicStream(mus);
        }
    }

    if (isLoaded)
    {
        DrawRectangle(30, 30, 20, 60, BLACK);
        DrawRectangle(30 + 30 + 5, 30, 20, 60, BLACK);
        DrawRectangleRec(PauseBound, (Color){0});
        if (hoverButton(PauseBound) && isMouseClicked())
            mode = PAUSED;

        if (mode != PAUSED)
        {
            UpdateMusicStream(mus);
            curTime = GetMusicTimePlayed(mus);

            if (ti < count - 1 && curTime >= tokens[ti + 1].time)
                ti++;
        }

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

        if (mode == PAUSED)
        {
            Play.x = (GetScreenWidth() / 2) - (Play.width / 2);
            Play.y = (GetScreenHeight() / 2) - Play.height;
            Restart.x = Play.x;
            Restart.y = Play.y + Restart.height + 25; // Play.y + Setting.height + 25;
            Setting.x = Play.x;
            Setting.y = Restart.y + Setting.height + 25;
            pExit.x = Play.x;
            pExit.y = Setting.y + pExit.height + 25;
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 255 / 2});
            DrawRectangleRec(Play, PbutCol1);
            DrawRectangleRec(Setting, PbutCol2);
            DrawRectangleRec(pExit, PbutCol3);
            DrawRectangleRec(Restart, PbutCol4);
            DrawText(
                "GAME IS PAUSED",
                ((GetScreenWidth() / 2) - (MeasureText("GAME IS PAUSED", 50) / 2)),
                (GetScreenHeight() / 2) - (Play.y / 2),
                50,
                Tcolor);
            DrawText(
                "RESUME",
                Play.x + Play.width / 2 - MeasureText("RESUME", 35) / 2,
                Play.y + Play.height / 2 - MeasureTextHeight("RESIME", 35) / 2,
                35,
                Texcol);
            DrawText(
                "RESTART",
                Restart.x + Restart.width / 2 - MeasureText("RESTART", 35) / 2,
                Restart.y + Restart.height / 2 - MeasureTextHeight("RESTART", 35) / 2,
                35,
                Texcol);
            DrawText(
                "OPTIONS",
                Setting.x + Setting.width / 2 - MeasureText("OPTIONS", 35) / 2,
                Setting.y + Setting.height / 2 - MeasureTextHeight("OPTIONS", 35) / 2,
                35,
                Texcol);
            DrawText(
                "MAIN MENU",
                pExit.x + pExit.width / 2 - MeasureText("MAIN MENU", 35) / 2,
                pExit.y + pExit.height / 2 - MeasureTextHeight("MAIN MENU", 35) / 2,
                35,
                Texcol);

            if (hoverButton(Play))
                PbutCol1.a = 195;
            else
                PbutCol1.a = 255;

            if (hoverButton(Setting))
                PbutCol2.a = 195;
            else
                PbutCol2.a = 255;

            if (hoverButton(pExit))
                PbutCol3.a = 195;
            else
                PbutCol3.a = 255;

            if (hoverButton(Restart))
                PbutCol4.a = 195;
            else
                PbutCol4.a = 255;

            if (hoverButton(Play) && isMouseClicked())
            {
                mode = PLAYING;
                PlayMusicStream(mus);
            }
            if (hoverButton(Setting) && isMouseClicked())
                idk();
            if (hoverButton(pExit) && isMouseClicked())
            {
                StopMusicStream(mus);
                UnloadMusicStream(mus);

                isLoaded = false;
                seal = true;
                ti = 0;
                mode = NOT;
                option = NONE;
                enter = false;

                return true;
            }
            if (hoverButton(Restart) && isMouseClicked())
            {
                ti = 0;
                SeekMusicStream(mus, 0.0f);
                mode = PLAYING;
                PlayMusicStream(mus);
            }
        }
    }

    if (GetMusicTimePlayed(mus) >= GetMusicTimeLength(mus) - 0.1f)
    {
        StopMusicStream(mus);
        UnloadMusicStream(mus);
        isLoaded = false;
        seal = true;
        ti = 0;
        mode = NOT;
        option = NONE;
        enter = false;
        return true;
    }
    return false;
}