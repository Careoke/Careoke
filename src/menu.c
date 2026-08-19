#include "../headers/menu.h"
#include "../headers/utility.h"
#include "../headers/tinyfiledialogs.h"

Rectangle play = {0, 0, 400, 75};
Rectangle setting = {0, 0, 400, 75};
Rectangle credit = {0, 0, 400, 75};
Rectangle Exit = {0, 0, 400, 75};
Rectangle close = {0, 0, 50, 50};
Rectangle Discard1 = {0};
Rectangle Discard2 = {0};
Rectangle DropB1 = {0, 0, 0, 0};
Rectangle DropB2 = {0, 0, 0, 0};
Rectangle UrlBox = {0, 0, 0, 0};
Rectangle Subwindow = {0};
Rectangle ExitWindow = {0};
Rectangle ExitButton1 = {0};
Rectangle ExitButton2 = {0};

Card raylib = {0};
Card libtinyfiledialogs = {0};
Card Colorhunt = {0};
Card j1gggs = {0};

Image tmp_tRay = {0};
Image tmp_tLibtinyfiledialogs = {0};
Image tmp_tColorhunt = {0};
Image tmp_tJ1gggs = {0};

Texture2D tRay = {0};
Texture2D tLibtinyfiledialogs = {0};
Texture2D tColorhunt = {0};
Texture2D tJ1gggs = {0};

enum OPT option = NONE;
enum STATE mode = NOT;

bool isWindowFocus = false;
int errTime;
char *filePaths[MAX_FILEPATH_RECORDED] = {0};
int filePathCounter = 0;
char *tmpMp3Path = NULL;
char *tmpLrcPath = NULL;
const char *filters[] = {"*.mp3", "*.lrc"};
bool enter = false;
bool showExit = false;
bool DropBoxHovered = 0;

bool isMp3 = 0;
bool isLrc = 0;
int inMp3 = -1;
int inLrc = -1;
int Image_seal = 0;

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

void InitImages()
{
    ImageResize(
        &tmp_tRay,
        (int)MeasureTextHeight(raylib.Head, 30),
        (int)MeasureTextHeight(raylib.Head, 30));

    ImageResize(
        &tmp_tLibtinyfiledialogs,
        (int)MeasureTextHeight(libtinyfiledialogs.Head, 30),
        (int)MeasureTextHeight(libtinyfiledialogs.Head, 30));

    ImageResize(
        &tmp_tColorhunt,
        (int)MeasureTextHeight(Colorhunt.Head, 30),
        (int)MeasureTextHeight(Colorhunt.Head, 30));

    ImageResize(
        &tmp_tJ1gggs,
        (int)MeasureTextHeight(j1gggs.Head, 30),
        (int)MeasureTextHeight(j1gggs.Head, 30));

    tRay = LoadTextureFromImage(tmp_tRay);
    tLibtinyfiledialogs = LoadTextureFromImage(tmp_tLibtinyfiledialogs);
    tColorhunt = LoadTextureFromImage(tmp_tColorhunt);
    tJ1gggs = LoadTextureFromImage(tmp_tJ1gggs);

    UnloadImage(tmp_tJ1gggs);
    UnloadImage(tmp_tColorhunt);
    UnloadImage(tmp_tLibtinyfiledialogs);
    UnloadImage(tmp_tRay);
    Image_seal = 1;
}

void UnloadTimages()
{
    UnloadTexture(tColorhunt);
    UnloadTexture(tRay);
    UnloadTexture(tLibtinyfiledialogs);
    UnloadTexture(tJ1gggs);
}

enum OPT DrawPlay()
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        enter = false;
        return NONE;
    }

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

    if (mode == NOT)
        if (isLrc && isMp3 && filePathCounter == 2)
            mode = PLAYING;
    if (filePathCounter == 0)
    {
        inMp3 = -1;
        inLrc = -1;
        isLrc = 0;
        isMp3 = 0;
    }

    DropB1.x = 0 + 60;
    DropB1.y = ((GetScreenHeight() / 2) - (GetScreenHeight() - GetScreenHeight() * 0.7f)) + 100;
    DropB1.width = (GetScreenWidth() - 180) / 2;
    DropB1.height = (GetScreenHeight() - DropB1.y) - 50;
    Discard1.width = 70;
    Discard1.height = 70;
    Discard1.x = DropB1.x + DropB1.width - Discard1.width - 7;
    Discard1.y = DropB1.y + 7;
    DropB2.x = 60 + DropB1.width + 60;
    DropB2.y = DropB1.y;
    DropB2.width = (GetScreenWidth() - 180) / 2;
    DropB2.height = (GetScreenHeight() - DropB1.y) - 50;
    Discard2.width = 70;
    Discard2.height = 70;
    Discard2.x = DropB2.x + DropB2.width - Discard2.width - 7;
    Discard2.y = DropB2.y + 7;
    UrlBox.x = ((60 + 60 + DropB1.width) + DropB2.width / 2) - (MeasureText("Drop your Lrc file Here :D", 20) / 2);
    UrlBox.y = DropB2.y + (DropB2.height / 2) + 40 + 20,
    UrlBox.width = MeasureText("Drop your Lrc file Here :D", 20),
    UrlBox.height = 40;
    close.x = (GetScreenWidth() - GetScreenWidth() * 0.1f) + 50;
    close.y = (((GetScreenHeight() / 2) - (GetScreenHeight() - GetScreenHeight() * 0.1f) / 2)) + 50;

    if (inMp3 != -1 && filePaths[inMp3] && tmpMp3Path == NULL)
    {
        TraceLog(LOG_INFO, "%s", filePaths[inMp3]);
        if (DropB1.width <= MeasureText(GetFileName(filePaths[inMp3]), 40))
        {
            size_t size_tmpMp3Path = ((DropB1.width - MeasureText("...", 40)) / 40);
            tmpMp3Path = malloc(size_tmpMp3Path + 4);
            strncpy(tmpMp3Path, GetFileName(filePaths[inMp3]), size_tmpMp3Path);
            tmpMp3Path[size_tmpMp3Path] = '\0';
            strcat(tmpMp3Path, "...");
        }
        else
        {
            TraceLog(LOG_INFO, "%s", filePaths[inMp3]);
            tmpMp3Path = malloc(strlen(GetFileName(filePaths[inMp3])) + 1);
            strcpy(tmpMp3Path, GetFileName(filePaths[inMp3]));
        }
    }

    if (inLrc != -1 && filePaths[inLrc] && tmpLrcPath == NULL)
    {
        if (DropB1.width <= MeasureText(GetFileName(filePaths[inLrc]), 40))
        {
            size_t size_tmpLrcPath = ((DropB1.width - MeasureText("...", 40)) / 40);
            tmpLrcPath = malloc(size_tmpLrcPath + 4);
            strncpy(tmpLrcPath, GetFileName(filePaths[inLrc]), size_tmpLrcPath);
            tmpLrcPath[size_tmpLrcPath] = '\0';
            strcat(tmpLrcPath, "...");
        }
        else
        {
            tmpLrcPath = malloc(strlen(GetFileName(filePaths[inLrc])) + 1);
            strcpy(tmpLrcPath, GetFileName(filePaths[inLrc]));
        }
    }

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
    {
        DrawText(
            TextFormat("%s", tmpMp3Path),
            (60 + DropB1.width / 2) - (MeasureText(tmpMp3Path, 40) / 2),
            DropB1.y + (DropB1.height / 2),
            40,
            (Color){252, 249, 234, 255});
        DrawRectangleRec(Discard1, RED);
        DrawText(
            "X",
            (Discard1.x + Discard1.width / 2) - (MeasureText("X", 50) / 2),
            (Discard1.y + (Discard1.height / 2)) - (MeasureTextHeight("X", 50) / 2),
            50,
            BLACK);

        if (hoverButton(Discard1) && isMouseClicked())
        {
            free(filePaths[inMp3]);
            free(tmpMp3Path);
            filePaths[inMp3] = NULL;
            tmpMp3Path = NULL;
            filePathCounter--;
            inMp3 = -1;
            isMp3 = false;
        }
    }

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
        if (hoverButton(UrlBox) && isMouseClicked())
            OpenURL("https://lrclib.net/");
    }
    else
    {
        DrawText(
            TextFormat("%s", tmpLrcPath),
            ((60 + 60 + DropB1.width) + DropB2.width / 2) - (MeasureText(tmpLrcPath, 40) / 2),
            DropB2.y + (DropB2.height / 2),
            40,
            (Color){252, 249, 234, 255});
        DrawRectangleRec(Discard2, RED);
        DrawText(
            "X",
            (Discard2.x + Discard2.width / 2) - (MeasureText("X", 50) / 2),
            (Discard2.y + (Discard2.height / 2)) - (MeasureTextHeight("X", 50) / 2),
            50,
            BLACK);

        if (hoverButton(Discard2) && isMouseClicked())
        {
            free(filePaths[inLrc]);
            free(tmpLrcPath);
            filePaths[inLrc] = NULL;
            tmpLrcPath = NULL;
            filePathCounter--;
            inLrc = -1;
            inLrc = false;
        }
    }

    if ((hoverButton(DropB1) || hoverButton(DropB2)) && !hoverButton(Discard1) && !hoverButton(Discard2))
        DropBoxHovered = 1;
    else
        DropBoxHovered = 0;

    if (enter == true)
    {
        if (filePathCounter < 2 && DropBoxHovered && isMouseClicked())
        {
            char *tmpFilePaths = NULL;
            if (filePathCounter == 1)
            {
                tmpFilePaths = tinyfd_openFileDialog(
                    "Careoke - Pick your ammo",
                    "",
                    2,
                    filters,
                    ".mp3, .lrc",
                    0);
                if (tmpFilePaths != NULL)
                {
                    if (IsFileExtension(tmpFilePaths, ".mp3") || IsFileExtension(tmpFilePaths, ".lrc"))
                    {
                        if (!IsFileExtension(tmpFilePaths, GetFileExtension(filePaths[filePathCounter - 1])))
                        {
                            int pathLen = strlen(tmpFilePaths) + 1;
                            filePaths[filePathCounter] = RL_CALLOC(pathLen, sizeof(char));
                            strcpy(filePaths[filePathCounter], tmpFilePaths);
                            if (!IsFileExtension(filePaths[filePathCounter], ".mp3"))
                            {
                                isLrc = 1;
                                inMp3 = 1;
                                inLrc = 0;
                            }
                            else
                            {
                                isMp3 = 1;
                                inMp3 = 0;
                                inLrc = 1;
                            }
                            filePathCounter++;
                        }
                    }
                    else
                    {
                        errTime = 3000.0f;
                    }
                }
            }

            if (filePathCounter == 0)
            {
                tmpFilePaths = tinyfd_openFileDialog(
                    "Careoke - Pick your ammo",
                    "",
                    2,
                    filters,
                    ".mp3, .lrc",
                    1);
                if (tmpFilePaths != NULL)
                {
                    if (memchr(tmpFilePaths, '|', strlen(tmpFilePaths)))
                    {
                        char *currentPath1 = strtok(tmpFilePaths, "|");
                        char *currentPath2 = strtok(NULL, "|");
                        if (((IsFileExtension(currentPath1, ".mp3") || IsFileExtension(currentPath1, ".lrc"))) || (IsFileExtension(currentPath2, ".mp3") || IsFileExtension(currentPath2, ".lrc")))
                        {
                            if (IsFileExtension(currentPath1, ".mp3") || IsFileExtension(currentPath1, ".lrc"))
                            {
                                int pathLen = strlen(currentPath1) + 1;
                                filePaths[filePathCounter] = RL_CALLOC(pathLen, sizeof(char));
                                strcpy(filePaths[filePathCounter], currentPath1);
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
                            }
                            if (IsFileExtension(currentPath2, ".mp3") || IsFileExtension(currentPath2, ".lrc"))
                            {
                                int pathLen = strlen(currentPath2) + 1;
                                filePaths[filePathCounter] = RL_CALLOC(pathLen, sizeof(char));
                                strcpy(filePaths[filePathCounter], currentPath2);
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
                            }
                        }
                        else
                            errTime = 3000.0f;
                    }
                    else
                    {
                        if ((IsFileExtension(tmpFilePaths, ".mp3") || IsFileExtension(tmpFilePaths, ".lrc")))
                        {
                            int pathLen = strlen(tmpFilePaths) + 1;
                            filePaths[filePathCounter] = RL_CALLOC(pathLen, sizeof(char));
                            strcpy(filePaths[filePathCounter], tmpFilePaths);
                            if (!IsFileExtension(filePaths[filePathCounter], ".mp3"))
                            {
                                isLrc = 1;
                                inMp3 = 1;
                                inLrc = 0;
                            }
                            else
                            {
                                isMp3 = 1;
                                inMp3 = 0;
                                inLrc = 1;
                            }
                            filePathCounter++;
                        }
                        else
                            errTime = 3000.0f;
                    }
                }
            }
        }
    }

    if (errTime > 0)
    {
        ShowMessage("Please Insert a Valid file/ file format", 40, CENTER, RED, 20);
        errTime -= GetFrameTime();
    }

    enter = true;
    if (hoverButton(close) && isMouseClicked())
    {
        enter = false;
        return NONE;
    }
    return PLAY;
}

enum OPT DrawSett()
{
    if (IsKeyPressed(KEY_ESCAPE))
        return NONE;

    close.x = (GetScreenWidth() - GetScreenWidth() * 0.15f) + 50;
    close.y = (((GetScreenHeight() / 2) - (GetScreenHeight() - GetScreenHeight() * 0.15f) / 2)) + 50;

    DrawRectangleRec(Subwindow, (Color){100, 100, 100, 200});

    DrawText("X", (GetScreenWidth() - GetScreenWidth() * 0.15f) + 50, (((GetScreenHeight() / 2) - (GetScreenHeight() - GetScreenHeight() * 0.15f) / 2)) + 50, 50, BLACK);
    DrawRectangleRec(close, (Color){0, 0, 0, 0});
    if (hoverButton(close) && isMouseClicked())
        return NONE;
    return SETTINGS;
}

enum OPT DrawCre()
{
    if (IsKeyPressed(KEY_ESCAPE))
        return NONE;

    close.x = (GetScreenWidth() - GetScreenWidth() * 0.15f) + 50;
    close.y = (((GetScreenHeight() / 2) - (GetScreenHeight() - GetScreenHeight() * 0.15f) / 2)) + 50;

    raylib.Head = "Raylib: Graphics library";
    raylib.body = "Raylib is a simple graphic library or C, made by ray-san\nIt is used as the base of this game";
    raylib.rec = (Rectangle){
        Subwindow.x + 50,
        Subwindow.y + close.y + 50,
        MeasureText(raylib.body, 15) + 40,
        MeasureTextHeight(raylib.Head, 30) + MeasureTextHeight(raylib.body, 20) + 40,
    };
    raylib.CardColor = (Color){96, 116, 86, 255};
    raylib.TextColor = BLACK;

    libtinyfiledialogs.Head = "tinyfiledialogs";
    libtinyfiledialogs.body = "tiny file dialogs is libaray that allows you to make\nPop up dialouges, Like the file manager dialouges";
    libtinyfiledialogs.rec = (Rectangle){
        Subwindow.x + 50 + raylib.rec.width + 20,
        Subwindow.y + close.y + 50,
        MeasureText(libtinyfiledialogs.body, 15) + 40,
        MeasureTextHeight(libtinyfiledialogs.Head, 30) + MeasureTextHeight(libtinyfiledialogs.body, 20) + 40,
    };
    libtinyfiledialogs.CardColor = (Color){96, 116, 86, 255};
    libtinyfiledialogs.TextColor = BLACK;

    Colorhunt.Head = "ColorHunt";
    Colorhunt.body = "Color Hunt is an open collection of beautiful color palettes,\ncreated by Gal Shir. Most of the color here are taken from their pallets";
    Colorhunt.rec = (Rectangle){
        Subwindow.x + 50 + raylib.rec.width + 20 + libtinyfiledialogs.rec.width + 20,
        Subwindow.y + close.y + 50,
        MeasureText(Colorhunt.body, 15) + 40,
        MeasureTextHeight(Colorhunt.Head, 30) + MeasureTextHeight(Colorhunt.body, 20) + 40,
    };
    Colorhunt.CardColor = (Color){96, 116, 86, 255};
    Colorhunt.TextColor = BLACK;

    j1gggs.Head = "j1gggs";
    j1gggs.body = "j1gggs is a Music artist whom i am a very fan of The Backgroud Music\nis from 'From The Start(Mewofy)' By him";
    j1gggs.rec = (Rectangle){
        Subwindow.x + 50,
        Subwindow.y + close.y + 50 + raylib.rec.height + 20,
        MeasureText(j1gggs.body, 15) + 40,
        MeasureTextHeight(j1gggs.Head, 30) + MeasureTextHeight(j1gggs.body, 20) + 40,
    };
    j1gggs.CardColor = (Color){96, 116, 86, 255};
    j1gggs.TextColor = BLACK;

    if (Image_seal < 1)
    {

        InitImages();
        raylib.img = tRay;
        libtinyfiledialogs.img = tLibtinyfiledialogs;
        Colorhunt.img = tColorhunt;
        j1gggs.img = tJ1gggs;
    }

    DrawRectangleRec(Subwindow, (Color){100, 100, 100, 200});
    DrawCard(raylib);
    DrawCard(libtinyfiledialogs);
    DrawCard(Colorhunt);
    DrawCard(j1gggs);

    DrawText(
        "Devloped by Tillua467",
        credit.x + ((credit.width / 2) - MeasureText("Devloped by Tillua467", 50) / 2),
        close.y,
        50,
        BLACK);

    DrawText(
        "With the Help of....",
        credit.x + ((credit.width / 2) - MeasureText("With Help of....", 50) / 2),
        close.y + 50 + 15, // close.y + font size of the previous text + padding
        40,
        BLACK);

    DrawText(
        "X",
        (GetScreenWidth() - GetScreenWidth() * 0.15f) + 50,
        (((GetScreenHeight() / 2) - (GetScreenHeight() - GetScreenHeight() * 0.15f) / 2)) + 50, // + padding
        50,
        BLACK);

    // Close bound box
    DrawRectangleRec(close, (Color){0, 0, 0, 0});
    if (hoverButton(close) && isMouseClicked())
        return NONE;
    return CREDIT;
}

int DrawPlayMenu()
{
    if (!isWindowFocus && WindowShouldClose())
        showExit = true;
    Subwindow.x = (((GetScreenWidth() / 2) - (GetScreenWidth() - GetScreenWidth() * 0.15f) / 2));
    Subwindow.y = (((GetScreenHeight() / 2) - (GetScreenHeight() - GetScreenHeight() * 0.15f) / 2));
    Subwindow.width = (GetScreenWidth() - GetScreenWidth() * 0.15f);
    Subwindow.height = (GetScreenHeight() - GetScreenHeight() * 0.15f);

    if (mode != NOT)
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

    if (!showExit)
    {
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

        if (isMouseClicked())
        {
            if (hoverButton(play))
                option = PLAY;
            if (hoverButton(setting))
                option = SETTINGS;
            if (hoverButton(credit))
                option = CREDIT;
            if (hoverButton(Exit))
                showExit = true;
        }
    }

    if (showExit)
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 255 / 1.5});
        ExitWindow.width = GetScreenHeight() * 0.75f;
        ExitWindow.height = GetScreenHeight() * 0.20f;
        ExitWindow.x = GetScreenWidth() / 2 - ExitWindow.width / 2;
        ExitWindow.y = GetScreenHeight() / 2 - ExitWindow.height / 2;
        ExitButton1.width = ExitWindow.width * 0.35f;
        ExitButton2.width = ExitButton1.width;
        ExitButton1.height = ExitWindow.height * 0.25f;
        ExitButton2.height = ExitButton1.height;
        ExitButton1.y = ExitWindow.y + ExitWindow.height - ExitButton1.height - 20;
        ExitButton2.y = ExitButton1.y;
        ExitButton1.x = ExitWindow.x + 35;
        ExitButton2.x = ExitButton1.x + ExitButton1.width + 60;

        DrawRectangleRec(
            ExitWindow,
            (Color){101, 146, 135, 255});

        DrawText(
            "Would you Like to Exit?",
            ExitWindow.x + 35,
            ExitWindow.y + 35,
            50,
            (Color){177, 211, 185, 255});

        DrawRectangleRec(ExitButton1, ExitButcol1);
        DrawText(
            "Exit",
            ExitButton1.x + ((ExitButton1.width / 2) - MeasureText("Exit", 40) / 2),
            ExitButton1.y + ((ExitButton1.height / 2) - MeasureTextHeight("Exit", 40) / 2),
            40,
            (Color){255, 229, 191, 255});
        DrawRectangleRec(ExitButton2, ExitButcol2);
        DrawText(
            "Cancle",
            ExitButton2.x + ((ExitButton2.width / 2) - MeasureText("Cancle", 40) / 2),
            ExitButton2.y + ((ExitButton2.height / 2) - MeasureTextHeight("Cancle", 40) / 2),
            40,
            (Color){255, 229, 191, 255});

        if (hoverButton(ExitButton1))
            ExitButcol1.a = 200;
        else if (hoverButton(ExitButton2))
            ExitButcol2.a = 200;
        else
        {
            ExitButcol1.a = 255;
            ExitButcol2.a = 255;
        }

        if (hoverButton(ExitButton1) && isMouseClicked())
            return 1;
        if (hoverButton(ExitButton2) && isMouseClicked())
            showExit = false;
    }

    if (mode == NOT)
    {
        if (option == PLAY)
            option = DrawPlay();
        else if (option == SETTINGS)
            option = DrawSett();
        else if (option == CREDIT)
            option = DrawCre();
        else
            idk();
    }

    return 0;
}