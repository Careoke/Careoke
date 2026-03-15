#include "../headers/tokenizer.h"

int GetLRC(char *lrcFile, Token tokens[])
{
    FILE *f = fopen(lrcFile, "r");

    char line[512];
    int count = 0;

    while (fgets(line, sizeof(line), f))
    {
        int min;
        float sec;
        char lyric[MAX_LYRIC];

        if (sscanf(line, "[%d:%f]%[^\n]", &min, &sec, lyric) == 3)
        {
            tokens[count].time = min * 60 + sec;
            strcpy(tokens[count].lyric, lyric);
            count++;
        }
    }

    fclose(f);
    return count;
}

int main()
{
    Token tokens[MAX_LINES];

    int count = GetLRC("out/lyrics.lrc", tokens);

    for (int i = 0; i < count; i++)
    {
        printf("%f -> %s\n", tokens[i].time, tokens[i].lyric);
    }

    return 0;
}