
#include "inverted_search.h"

int search_database(main_t *hash_table[27], char *word)
{
    if (hash_table == NULL || word == NULL || word[0] == '\0')
    {
        printf("Invalid Search input.\n");
        return FAILURE;
    }

    normalize_word(word);

    int index = get_hash_index(word);

    if (index == FAILURE)
    {
        return FAILURE;
    }

    main_t *main_temp = hash_table[index];

    while (main_temp != NULL)
    {
        if (strcmp(main_temp->word, word) == 0)
        {
            sub_t *sub_temp = main_temp->sub_link;

            printf("\n");
            printf("+--------------------+------------+------------------------------+------------+\n");
            printf("| Word               | File Count | Filename                     | Word Count |\n");
            printf("+--------------------+------------+------------------------------+------------+\n");

            while (sub_temp != NULL)
            {
                printf("| %-18s | %-10d | %-28s | %-10d |\n",
                       main_temp->word,
                       main_temp->file_count,
                       sub_temp->file_name,
                       sub_temp->word_count);

                sub_temp = sub_temp->sub_link;
            }

            printf("+--------------------+------------+------------------------------+------------+\n");

            return SUCCESS;
        }

        main_temp = main_temp->main_link;
    }

    printf("The word is not available.\n");

    return FAILURE;
}
