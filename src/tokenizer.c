#include "../headers/tokenizer.h"

void FreeTokens(Token **tokens, int count)
{
    if (!tokens || !*tokens)
        return;

    for (int i = 0; i < count; i++)
        free((*tokens)[i].lyric);

    free(*tokens);
    *tokens = NULL;
}

int GetLRC(char *lrcFile, Token **tokens)
{
    FILE *f = fopen(lrcFile, "r");
    if (!f)
        return 0;

    char *Line;
    int count = 0;
    *tokens = NULL;

    for (;;)
    {
        Line = ReadFileStream(f, 1);

        if (!Line)
            break;

        char *buff = strstr(Line, "]");
        if (buff)
        {
            *buff = '\0';

            int min;
            float sec;

            if (sscanf(Line, "[%d:%f]", &min, &sec) == 2)
            {
                Token *tmp = realloc(*tokens, (count + 1) * sizeof(Token));
                if (!tmp)
                    break;
                *tokens = tmp;

                (*tokens)[count].time = min * 60 + sec;
                (*tokens)[count].lyric = malloc(strlen(buff + 2) + 1);

                if (!(*tokens)[count].lyric)
                    break;

                strcpy((*tokens)[count].lyric, buff + 2);
                count++;
            }
        }

        free(Line);
    }

    fclose(f);
    return count;
}