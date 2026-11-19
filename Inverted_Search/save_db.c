#include "inverted_search.h"

int save_database(main_t *hash_table[27],char *file_name)
{
    FILE *fp = fopen(file_name,"w");
    if(fp == NULL)
    {
        printf("File is not opening\n");
        return FAILURE;
    }
    for(int index = 0 ;index < 27; index++)
    {
        main_t *main_temp = hash_table[index];
        

        while(main_temp != NULL)
        {
            sub_t *sub_temp = main_temp->sub_link;
            while(sub_temp != NULL)
            {
                fprintf(fp, "%s %d %s %d\n",main_temp->word,main_temp->file_count,sub_temp->file_name,sub_temp->word_count);
                sub_temp = sub_temp->sub_link;
            }
            main_temp = main_temp->main_link;
        }
    }
    fclose(fp);
    return SUCCESS;
}