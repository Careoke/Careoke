#include "../headers/tokenizer.h"

int GetLRC(char *lrcFile, Token tokens[])
{
    FILE *f = fopen(lrcFile, "r");
    if (!f)
        return 0;

    char *Line;
    int count = 0;
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
                tokens[count].time = min * 60 + sec;
                strcpy(tokens[count].lyric, buff + 2);
                count++;
            }
        }

        free(Line);
    }

    fclose(f);
    return count;
}