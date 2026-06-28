#ifndef MENU_H
#define MENU_H

#define MAX_FILEPATH_RECORDED 2

#include <raylib.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief a enum that holds the current state of the game
 *
 * @var START when the game hasn't started yet
 *
 * @var PLAYING when the game is started
 *
 * @var PAUSED when the game is started but paused
 */
enum STATE
{
    START,
    PLAYING,
    PAUSED
};

/**
 * @brief a enum that holds the options for the player to choose before the game starts
 *
 * @var PLAY when the game has started (or the STATE sate is PLAYING)
 *
 * @var SETTINGS when the user open the settings subwindow
 *
 * @var CREDIT when the user open the credit subwindow
 *
 * @var NONE whent the user hasn't selected any options
 */
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

/**
 * @brief does nothing
 *
 * @saying i guess using 'continue' will be a better option but idk
 */
void idk();
/**
 * @brief initialize the Images needed Also turns Those images into Textures
 */
void InitImages();
/**
 *  @brief Unload the Texture Images that were initialize with InitImages()
 */
void UnloadTimages();
/**
 * @brief Draws the play window
 *
 * @saying tho it isn't play it's the selection windows
 *
 * @warning this function also handels the user input of the files
 * @warning although it doesn't take any values as input but a filePaths(poniter) and a filePathCounter is must
 *
 * @returns Return the 'state' and 'option' of the game or should the game close or not
 */
enum OPT DrawPlay();
/**
 * @brief Draws settings subwindows
 *
 * @returns Return the 'option' of the game
 */
enum OPT DrawSett();
/**
 * @brief Draws credit subwindows
 *
 * @returns Return the 'option' of the game
 */
enum OPT DrawCre();
/**
 * @brief Draws the mainmenu of the game
 *
 * @returns Returns a integer value (2 = game should start, 1 = game should exit, 0 = do nothing)
 */
int DrawPlayMenu();
void DrawPauseMenu();

#endif // !MENU_H