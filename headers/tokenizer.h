#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/parser.h"

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
    char *lyric;
} Token;

void FreeTokens(Token **tokens, int count);

/**
 * @brief Takes a *.lrc file and put the contents as Token
 *
 * @return Return the number of lyrics
 */
int GetLRC(char *lrcFile, Token **token);

#endif // !TOKENIZER_H