#include "inverted_search.h"

int read_and_validate(int argc, char *argv[],node_ht **head)
{     
    for(int i = 1;i < argc; i++)
    {
        for(int j = i+1; j < argc;j++)
        {
        if(strcmp(argv[i],argv[j])==0)
        {
            printf("Both files are same\n");
            return FAILURE;
        }
        }
    }
    for(int i = 1; i<argc;i++)
    {
    
        FILE *fp = fopen(argv[i],"r");
        if(fp == NULL)
        {
            printf("File Opening Failed.\n");
            return FAILURE;
        }
        else
        {
            printf("File Opened Successfully\n");
        }
        if(fseek(fp, 0, SEEK_END) != 0)
        {
            fclose(fp);
            return FAILURE;
        }

        long size = ftell(fp);

        if(size == -1L)
        {
            fclose(fp);
            return FAILURE;
        }

        if(size == 0)
        {
            printf("File is Empty\n");
            fclose(fp);
            return FAILURE;
        }
        rewind(fp);
        fclose(fp);

        node_ht *new = malloc(sizeof(node_ht));
        if(new == NULL)
        {
            printf("Memory Allocation Failed\n");
            return FAILURE;
        }
        if (strlen(argv[i]) >= sizeof(new->f_name))
        {
            printf("Filename too long\n");
            free(new);
            return FAILURE;
        }
        strcpy(new->f_name,argv[i]);
        new->link = NULL;

        if(*head == NULL)
        {
            *head = new;
        }
        else
        {
        node_ht *temp = *head;

        while(temp->link != NULL)
        {
            temp = temp->link;
        }
        temp->link = new;
        }
    }    
    
    return SUCCESS;
}

