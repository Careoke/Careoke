#ifndef UTILITY
#define UTILITY

#include <stdbool.h>
#include <stdio.h>
#include <raylib.h>

/**
 * @brief a enum that holds postions to show a dialouge
 */
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

/**
 * @brief Take a Rectangle rec and checks if there was a collision between the rectangle and mouse
 *
 * @warning only rectangle shape
 *
 * @return Return true if there is a collision
 */
bool hoverButton(Rectangle rec);

/**
 * @brief Shows a Dialouge with a message
 *
 * @var msg The message
 *
 * @var padding around the text
 *
 * @var pos Postions of subwindow
 *
 * @var col Color of the window
 *
 * @var fontSize Size of the font
 *
 * @warning fixed Postions
 */
void ShowMessage(const char *msg, int padding, Postions pos, Color col, int fontSize);

#endif // !UTILITY