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

/**
 * @brief a struct that hold the parameters to draw a card
 */
typedef struct Card
{
    Rectangle rec;
    Texture2D img;
    char *Head;
    char *body;
    Color CardColor;
    Color TextColor;
} Card;

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
extern Color ExitButcol1;
extern Color ExitButcol2;
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

/**
 * @brief Shows the height(y) value of a Text with his font size
 *
 * @var any text (can have \n)
 *
 * @var font size in int
 *
 * @return Returns the Height(y) of a Text
 */
float MeasureTextHeight(char *text, int fontSize);

/**
 * @brief Draw a using `Card` struct
 *
 * @var Takes a `Card` value
 *
 * @return Returns True if the mouse hoverd on the card
 */
bool DrawCard(Card card);

#endif // !UTILITY