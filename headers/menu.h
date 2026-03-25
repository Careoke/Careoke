#ifndef MENU_H
#define MENU_H

#include <raylib.h>

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

void idk();
void DrawPlay();
enum OPT DrawSett();
enum OPT DrawCre();
void DrawPlayMenu();
void DrawPauseMenu();

#endif // !MENU_H