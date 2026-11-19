#include "inverted_search.h"

int get_hash_index(const char *word)
{
    if (word == NULL || word[0] == '\0')
    {
        return FAILURE;
    }

    unsigned char ch = (unsigned char)word[0];

    if (ch >= 'A' && ch <= 'Z')
    {
        ch = ch + ('a' - 'A');
    }

    if (ch >= 'a' && ch <= 'z')
    {
        return ch - 'a' + 1;
    }

    return 0;
}

void normalize_word(char *word)
{
    if (word == NULL)
    {
        return;
    }

    for (int i = 0; word[i] != '\0'; i++)
    {
        word[i] = (char)tolower((unsigned char)word[i]);
    }
}