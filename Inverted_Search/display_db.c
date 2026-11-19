
#include "inverted_search.h"

int display_database(main_t *hash_table[27])
{
    main_t *main_temp;
    sub_t *sub_temp;
    int found = 0;

    printf("\n");
    printf("+--------+--------------------+------------+------------------------------+------------+\n");
    printf("| Index  | Word               | File Count | Filename                     | Word Count |\n");
    printf("+--------+--------------------+------------+------------------------------+------------+\n");

    for (int index = 0; index < 27; index++)
    {
        main_temp = hash_table[index];

        while (main_temp != NULL)
        {
            sub_temp = main_temp->sub_link;

            while (sub_temp != NULL)
            {
                found = 1;

                printf("| %-6d | %-18s | %-10d | %-28s | %-10d |\n",
                       index,
                       main_temp->word,
                       main_temp->file_count,
                       sub_temp->file_name,
                       sub_temp->word_count);

                sub_temp = sub_temp->sub_link;
            }

            main_temp = main_temp->main_link;
        }
    }

    printf("+--------+--------------------+------------+------------------------------+------------+\n");

    if (found == 0)
    {
        printf("Database is empty.\n");
        return FAILURE;
    }

    return SUCCESS;
}
