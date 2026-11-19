
#include "inverted_search.h"

void free_database(main_t *hash_table[27])
{
    main_t *main_temp;
    main_t *next_main;
    sub_t *sub_temp;
    sub_t *next_sub;

    for (int index = 0; index < 27; index++)
    {
        main_temp = hash_table[index];

        while (main_temp != NULL)
        {
            next_main = main_temp->main_link;

            sub_temp = main_temp->sub_link;

            while (sub_temp != NULL)
            {
                next_sub = sub_temp->sub_link;
                free(sub_temp);
                sub_temp = next_sub;
            }

            free(main_temp);
            main_temp = next_main;
        }

        hash_table[index] = NULL;
    }
}


void free_file_list(node_ht **head)
{
    if (head == NULL)
    {
        return;
    }

    node_ht *temp = *head;

    while (temp != NULL)
    {
        node_ht *next = temp->link;

        free(temp);

        temp = next;
    }

    *head = NULL;
}
