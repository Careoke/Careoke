#ifndef MENU_H
#define MENU_H

#include <raylib.h>

enum STATE
{
    START,
    PLAYING,
    PAUSED
};

void DrawPlayMenu();
void DrawPauseMenu();

#endif // !MENU_H