#include "inverted_search.h"


#include "inverted_search.h"

int update_database(main_t *hash_table[27], node_ht **head, char *file_name)
{
    FILE *fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        printf("Database file is not opened\n");
        return FAILURE;
    }

    char word[50];
    char input_file[MAX_FILE_NAME];
    int file_count;
    int word_count;

    while (fscanf(fp, "%49s %d %99s %d",
                  word, &file_count, input_file, &word_count) == 4)
    {
        normalize_word(word);
        int index = get_hash_index(word);
        if(index == FAILURE)
        {
            fclose(fp);
            return FAILURE;
        }

        

        // Search for Main Node
        main_t *main_temp = hash_table[index];

        while (main_temp != NULL)
        {
            if (strcmp(main_temp->word, word) == 0)
            {
                break;
            }

            main_temp = main_temp->main_link;
        }

        // Main Node does not exist
        if (main_temp == NULL)
        {
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

            // Create Sub Node
            sub_t *new_sub = malloc(sizeof(sub_t));

            if (new_sub == NULL)
            {
                free(new_main);
                fclose(fp);
                return FAILURE;
            }

            strcpy(new_sub->file_name, input_file);
            new_sub->word_count = word_count;
            new_sub->sub_link = NULL;

            new_main->sub_link = new_sub;

            hash_table[index] = new_main;
        }
        else
        {
            // Main Node exists: search Sub Node
            sub_t *sub_temp = main_temp->sub_link;

            while (sub_temp != NULL)
            {
                if (strcmp(sub_temp->file_name, input_file) == 0)
                {
                    break;
                }

                sub_temp = sub_temp->sub_link;
            }

            // Filename does not exist
            if (sub_temp == NULL)
            {
                sub_t *new_sub = malloc(sizeof(sub_t));

                if (new_sub == NULL)
                {
                    fclose(fp);
                    return FAILURE;
                }

                strcpy(new_sub->file_name, input_file);
                new_sub->word_count = word_count;
                new_sub->sub_link = main_temp->sub_link;

                main_temp->sub_link = new_sub;
                main_temp->file_count++;
            }
        }
    }

    fclose(fp);

    return SUCCESS;
}
