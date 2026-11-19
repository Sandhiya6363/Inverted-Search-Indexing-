#include "inverted_search.h"
/*Done by Sandhiya.S
Description :Developed an Inverted Search application in C 
using hash tables and linked lists to efficiently index and 
search words across multiple text files. 
    Implemented database creation, display, search, update, 
and save operations with file handling and dynamic memory
 management.*/

main_t *hash_table[27] = {NULL};
int main(int argc, char *argv[])
{
    node_ht *head = NULL;
    if(argc <= 1)
    {
        printf("Please provide input files\n");
        return FAILURE;
    }

    if(read_and_validate(argc, argv,&head)== SUCCESS)
    {
        printf("File Validation Successfully\n");
    }
    else
    {
        printf("File Validation Failed\n");
        return FAILURE;
    }
    int choice;
    char word[50];
    char file_name[MAX_FILE_NAME];
    int flag = 0;

    do
    {
    printf("=================INVERTED SEARCH================\n");
    printf("1.Create Database\n2.Display Database\n3.Search Database\n4.Save Database\n5.Update Database\n6.Exit\n");
    if (scanf("%d", &choice) != 1)
    {
    printf("Invalid input\n");
    return FAILURE;
    }

    switch(choice)
    {
        case 1:
        {
        if(flag)
        {
            printf("Database creation has already been attempted.\n");
            printf("Restart the program to try again.\n");
            break;
        }
        flag = 1;

        if(create_database(head,hash_table)== SUCCESS)
        printf("Create Database is Successfully completed\n");
        break;
        }
        case 2:
        if(display_database(hash_table)== SUCCESS)
        {
            printf("Display the database is successfully completed\n");
        }
        break;

        case 3:
        printf("Enter the word to search:\n");
        scanf("%49s",word);
        if(search_database(hash_table,word)==SUCCESS)
        {
            printf("Search Database is successfully implemented\n");
        }
        break;

        case 4:
        printf("Enter the Filename:\n");
        scanf("%99s",file_name);
        if(save_database(hash_table,file_name) == SUCCESS)
        {
            printf("The database is saved successfully\n");
        }
        break;

        case 5:
        printf("Enter the Filename:\n");
        scanf("%99s",file_name);
        if(update_database(hash_table,&head,file_name)==SUCCESS)
        {
            printf("Updation is successfully completed\n");
        }
        break;

        case 6:
        return SUCCESS;

        default:
        printf("Invalid choice\n");
        break;

    }
    }while(choice != 6);
    free_database(hash_table);
    free_file_list(&head);
    return SUCCESS;

}



