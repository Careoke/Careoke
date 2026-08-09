#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include <stdbool.h>
#include "../headers/tokenizer.h"
#include "../headers/menu.h"
#include "../headers/utility.h"

/**
 * @brief the player of the game
 *
 * @return returns true when the music has ended
 */
bool Player(char *musicDir, char *lrcDir);

#endif