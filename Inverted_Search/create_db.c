#include "inverted_search.h"

int create_database(node_ht *head, main_t *hash_table[27])
{
    if(head == NULL || hash_table == NULL)
    {
        printf("Invalid database input.\n");
        return FAILURE;
    }
    node_ht *temp = head;

    while (temp != NULL)
    {
        FILE *fp = fopen(temp->f_name, "r");

        if (fp == NULL)
        {
            return FAILURE;
        }

        if (strlen(temp->f_name) >= sizeof(((sub_t *)0)->file_name))
        {
            fclose(fp);
            return FAILURE;
        }

        char word[50];

        while (fscanf(fp, "%49s", word) == 1)
        {
            normalize_word(word);
            int index = get_hash_index(word);

            if(index == FAILURE)
            {
                fclose(fp);
                return FAILURE;
            }

            // Search for the word in Main Node list
            main_t *flag = hash_table[index];

            while (flag != NULL)
            {
                if (strcmp(flag->word, word) == 0)
                {
                    break;
                }

                flag = flag->main_link;
            }

            // Word already exists
            if (flag != NULL)
            {
                sub_t *sub_temp = flag->sub_link;

                // Search filename in Sub Node list
                while (sub_temp != NULL)
                {
                    if (strcmp(sub_temp->file_name, temp->f_name) == 0)
                    {
                        break;
                    }

                    sub_temp = sub_temp->sub_link;
                }

                // Filename already exists
                if (sub_temp != NULL)
                {
                    sub_temp->word_count++;
                }
                else
                {
                    // Create the new Sub Node
                    sub_t *new_sub = malloc(sizeof(sub_t));

                    if (new_sub == NULL)
                    {
                        fclose(fp);
                        return FAILURE;
                    }

                    strcpy(new_sub->file_name, temp->f_name);
                    new_sub->word_count = 1;

                    new_sub->sub_link = flag->sub_link;
                    flag->sub_link = new_sub;

                    flag->file_count++;
                }
            }
            else
            {
                // Create new Main Node
                main_t *new_main = malloc(sizeof(main_t));

                if (new_main == NULL)
                {
                    fclose(fp);
                    return FAILURE;
                }

                strcpy(new_main->word, word);
                new_main->file_count = 1;
                new_main->main_link = hash_table[index];
                new_main->sub_link = NULL;

                // Create first Sub Node
                sub_t *new_sub = malloc(sizeof(sub_t));

                if (new_sub == NULL)
                {
                    free(new_main);
                    fclose(fp);
                    return FAILURE;
                }

                strcpy(new_sub->file_name, temp->f_name);
                new_sub->word_count = 1;
                new_sub->sub_link = NULL;

                new_main->sub_link = new_sub;

                // Insert Main Node into hash table
                hash_table[index] = new_main;
            }
        }

        fclose(fp);

        // Move to next filename
        temp = temp->link;
    }

    return SUCCESS;
}