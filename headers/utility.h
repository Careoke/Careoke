#ifndef UTILITY
#define UTILITY

#include <stdbool.h>
#include <stdio.h>
#include <raylib.h>

typedef enum
{
    TOP_LEFT,
    TOP_MIDDLE,
    TOP_RIGHT,
    CENTER,
    BOTTOM_MIDDLE,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
} Postions;

extern Color Ccol;
extern Color Bocol;
extern Color Mencol;
extern Color Tcol;
extern Color Pcol;
extern Color Butcol1;
extern Color Butcol2;
extern Color Butcol3;
extern Color Butcol4;
extern Color Textcol;

bool hoverButton(Rectangle rec);
void ShowMessage(const char *msg, int padding, Postions pos, Color col, int fontSize);

#endif // !UTILITY