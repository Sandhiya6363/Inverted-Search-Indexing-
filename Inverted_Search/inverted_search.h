#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#define MAX_FILE_NAME 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include <ctype.h>


#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
    char f_name[MAX_FILE_NAME];
    struct node *link;
}node_ht;

// typedef struct hash_table
// {
//     int index;
//     struct hash_table *h_link; 

// }hash_t;


typedef struct sub_node
{
    char file_name[MAX_FILE_NAME];
    int word_count;
    struct sub_node *sub_link;
}sub_t;

typedef struct main_node
{
    int file_count;
    char word[50];
    struct main_node *main_link;
    sub_t *sub_link;
}main_t;

extern main_t *hash_table[27];
//main_t *hash_table[27] = {NULL};


int read_and_validate(int argc, char *argv[], node_ht **head);

int create_database(node_ht *head, main_t *hash_table[27]);

int display_database(main_t *hash_table[27]);

int search_database(main_t *hash_table[27], char *word);

int save_database(main_t *hash_table[27], char *file_name);

int update_database(main_t *hash_table[27], node_ht **head,
                    char *file_name);

int get_hash_index(const char *word);

void normalize_word(char *word);

void free_database(main_t *hash_table[27]);

void free_file_list(node_ht **head);

#endif

