#ifndef MENU_H
#define MENU_H

#include <raylib.h>
#include <stdlib.h>

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

void idk();
enum OPT DrawPlay();
enum OPT DrawSett();
enum OPT DrawCre();
int DrawPlayMenu();
void DrawPauseMenu();

#endif // !MENU_H