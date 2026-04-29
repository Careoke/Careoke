#include "../headers/menu.h"
#include "../headers/utility.h"

Rectangle play = {0, 0, 400, 75};
Rectangle setting = {0, 0, 400, 75};
Rectangle credit = {0, 0, 400, 75};
Rectangle Exit = {0, 0, 400, 75};
Rectangle close = {0, 0, 50, 50};
Rectangle DropB1 = {0, 0, 0, 0};
Rectangle DropB2 = {0, 0, 0, 0};
Rectangle UrlBox = {0, 0, 0, 0};

enum OPT option = NONE;
enum STATE mode = START;

bool isWindowFocus = false;
int errTime;
char *filePaths[MAX_FILEPATH_RECORDED] = {0};
int filePathCounter = 0;

bool isMp3 = 0;
bool isLrc = 0;
int inMp3 = 0;
int inLrc = 1;

/*
EXPLANANTION:

1.Why DropB1.width = (GetScreenWidth() - 180) / 2;;
    so the Drop Box will have a 60px padding from both side of the window bcz of that 2 Box will look like this
    |----------------------|
    |60|--x--|60|--x--| 60|      so if we do the math
    |60|--x--|60|--x--| 60|      60 + x + 60 + x + 60 = GetScreenWidth()
    |---------------------|         and so the x = (GetScreenWidth() - 180) / 2
    <--GetScreenWidth()-->
*/

void idk()
{
    // i don't know
}

enum OPT DrawPlay()
{
    if (IsFileDropped())
    {
        FilePathList droppedFiles = LoadDroppedFiles();

        for (int i = 0; i < (int)droppedFiles.count; i++)
        {
            if (filePathCounter < MAX_FILEPATH_RECORDED)
            {
                const char *currentPath = droppedFiles.paths[i];

                if (IsFileExtension(currentPath, ".mp3") || IsFileExtension(currentPath, ".lrc"))
                {
                    if (IsFileExtension(currentPath, ".mp3") && isMp3)
                        errTime = 3000.0f;
                    else if (IsFileExtension(currentPath, ".lrc") && isLrc)
                        errTime = 3000.0f;
                    else
                    {
                        int pathLen = strlen(currentPath) + 1;
                        if (filePaths[filePathCounter] != NULL)
                            RL_FREE(filePaths[filePathCounter]);
                        filePaths[filePathCounter] = (char *)RL_CALLOC(pathLen, sizeof(char));
                        strcpy(filePaths[filePathCounter], currentPath);
                        if (!IsFileExtension(filePaths[filePathCounter], ".mp3"))
                        {
                            isLrc = 1;
                            inMp3 = 1;
                            inLrc = 0;
                        }
                        else
                        {
                            isMp3 = 1;
                        }
                        filePathCounter++;
                        TraceLog(LOG_INFO, "%s", currentPath);
                    }
                }
                else
                {
                    errTime = 3000.0f;
                }
            }
        }
        UnloadDroppedFiles(droppedFiles);
    }

    if (isLrc && isMp3 && filePathCounter == 2)
        mode = PLAYING;

    DropB1.x = 0 + 60;
    DropB1.y = ((GetScreenHeight() / 2) - (GetScreenHeight() - GetScreenHeight() * 0.7f)) + 100;
    DropB1.width = (GetScreenWidth() - 180) / 2;
    DropB1.height = (GetScreenHeight() - DropB1.y) - 50;
    DropB2.x = 60 + DropB1.width + 60;
    DropB2.y = DropB1.y;
    DropB2.width = (GetScreenWidth() - 180) / 2;
    DropB2.height = (GetScreenHeight() - DropB1.y) - 50;
    UrlBox.x = ((60 + 60 + DropB1.width) + DropB2.width / 2) - (MeasureText("Drop your Lrc file Here :D", 20) / 2);
    UrlBox.y = DropB2.y + (DropB2.height / 2) + 40 + 20,
    UrlBox.width = MeasureText("Drop your Lrc file Here :D", 20),
    UrlBox.height = 40;
    close.x = (GetScreenWidth() - GetScreenWidth() * 0.1f) + 50;
    close.y = (((GetScreenHeight() / 2) - (GetScreenHeight() - GetScreenHeight() * 0.1f) / 2)) + 50;

    DrawRectangle(
        0,
        0,
        GetScreenWidth(),
        GetScreenHeight(),
        (Color){151, 168, 122, 255});

    DrawText(
        "X",
        (GetScreenWidth() - GetScreenWidth() * 0.1f) + 50,
        (((GetScreenHeight() / 2) - (GetScreenHeight() - GetScreenHeight() * 0.1f) / 2)) + 50,
        50, BLACK);
    DrawRectangleRec(close, (Color){0, 0, 0, 0});

    DrawText(
        "Let's Get Singing~!",
        ((GetScreenWidth() / 2) - (MeasureText("Let's Get Singing~!", 50) / 2)),
        ((GetScreenHeight() / 2) - (GetScreenHeight() - GetScreenHeight() * 0.7f)),
        50, Textcol);

    DrawRectangleRec(DropB1, (Color){191, 162, 140, 255 / 2});
    if (!isMp3)
        DrawRectangleLinesEx(
            DropB1,
            5,
            (Color){85, 94, 83, 255});
    else
        DrawRectangleLinesEx(
            DropB1,
            7,
            (Color){0, 128, 0, 255});
    if (!isMp3)
        DrawText(
            "Drop your Music Here :3",
            (60 + DropB1.width / 2) - (MeasureText("Drop your Music Here :3", 40) / 2),
            DropB1.y + (DropB1.height / 2),
            40,
            (Color){252, 249, 234, 255});
    else
        DrawText(
            TextFormat("%s", GetFileName(filePaths[inMp3])),
            (60 + DropB1.width / 2) - (MeasureText(TextFormat("%s", GetFileName(filePaths[inMp3])), 40) / 2),
            DropB1.y + (DropB1.height / 2),
            40,
            (Color){252, 249, 234, 255});

    DrawRectangleRec(DropB2, (Color){191, 162, 140, 255 / 2});
    if (!isLrc)
        DrawRectangleLinesEx(
            DropB2,
            5,
            (Color){85, 94, 83, 255});
    else
        DrawRectangleLinesEx(
            DropB2,
            7,
            (Color){0, 128, 0, 255});
    if (!isLrc)
    {
        DrawText(
            "Drop your Lrc file Here :D",
            ((60 + 60 + DropB1.width) + DropB2.width / 2) - (MeasureText("Drop your Lrc file Here :D", 40) / 2),
            DropB2.y + (DropB2.height / 2),
            40,
            (Color){252, 249, 234, 255});
        DrawText(
            "If you don't have an LRC file\n Look here (click to get it)",
            ((60 + 60 + DropB1.width) + DropB2.width / 2) - (MeasureText("If you don't have an LRC file\n Look here (click to get it)", 20) / 2),
            DropB2.y + (DropB2.height / 2) + 40 + 20,
            20,
            BLUE);
        DrawRectangleRec(
            UrlBox,
            (Color){0, 0, 0, 0});
        if (hoverButton(UrlBox) && (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
            OpenURL("https://lrclib.net/");
    }
    else
    {
        DrawText(
            TextFormat("%s", GetFileName(filePaths[inLrc])),
            ((60 + 60 + DropB1.width) + DropB2.width / 2) - (MeasureText(TextFormat("%s", GetFileName(filePaths[inLrc])), 40) / 2),
            DropB2.y + (DropB2.height / 2),
            40,
            (Color){252, 249, 234, 255});
    }

    if (errTime > 0)
    {
        ShowMessage("Please Insert a Valid file/ file format", 40, CENTER, RED, 20);
        errTime -= GetFrameTime();
    }

    if (hoverButton(close) && (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)))
        return NONE;
    return PLAY;
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

int DrawPlayMenu()
{
    if (mode == PLAYING)
        return 2;

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
    Exit.x = play.x;
    Exit.y = (GetScreenHeight() / 2) + (40 + 75 + 106 * 2);
    DrawRectangleRec(Exit, Butcol4);

    DrawText(
        "PLAY",
        play.x + ((play.width / 2) - MeasureText("PLAY", 50) / 2),
        play.y + 15,
        50, Textcol);
    DrawText(
        "SETTINGS",
        setting.x + ((setting.width / 2) - MeasureText("SETTINGS", 50) / 2),
        setting.y + 15,
        50, Textcol);
    DrawText(
        "CREDITS",
        credit.x + ((credit.width / 2) - MeasureText("CREDITS", 50) / 2),
        credit.y + 15,
        50, Textcol);
    DrawText(
        "EXIT",
        Exit.x + ((Exit.width / 2) - MeasureText("EXIT", 50) / 2),
        Exit.y + 15,
        50, Textcol);

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

        if (hoverButton(Exit))
            Butcol4.a = 150;
        else
            Butcol4.a = 255;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        if (hoverButton(play))
            option = PLAY;
        if (hoverButton(setting))
            option = SETTINGS;
        if (hoverButton(credit))
            option = CREDIT;
        if (hoverButton(Exit))
            return 1;
    }

    if (option == PLAY)
        option = DrawPlay();
    else if (option == SETTINGS)
        option = DrawSett();
    else if (option == CREDIT)
        option = DrawCre();
    else
        idk();

    return 0;
}