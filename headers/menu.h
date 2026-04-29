#ifndef MENU_H
#define MENU_H

#define MAX_FILEPATH_RECORDED 2

#include <raylib.h>
#include <stdlib.h>
#include <string.h>

enum STATE
{
    START,
    PLAYING,
    PAUSED
};

enum OPT
{
    PLAY,
    SETTINGS,
    CREDIT,
    NONE
};

extern enum OPT option;
extern enum STATE mode;

extern char *filePaths[MAX_FILEPATH_RECORDED];
extern int filePathCounter;

void idk();
enum OPT DrawPlay();
enum OPT DrawSett();
enum OPT DrawCre();
int DrawPlayMenu();
void DrawPauseMenu();

#endif // !MENU_H