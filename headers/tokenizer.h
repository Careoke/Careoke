#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LYRIC 256
#define MAX_LINES 100

/**
 * @brief a struct that holds the lrc file
 *
 * @var time is the time of lyric
 *
 * @var lyric is the lyrics
 */
typedef struct
{
    float time;
    char lyric[MAX_LYRIC];
} Token;

/**
 * @brief Takes a *.lrc file and put the contents as Token
 *
 * @warning This function doesn't allocate memory dynamiclly
 * it hard coded as normal song lyrics doesn't go higher than 256 characters
 * or 100 lines
 *
 * @return Return the number of lyrics
 */
int GetLRC(char *lrcFile, Token token[]);

#endif // !TOKENIZER_H