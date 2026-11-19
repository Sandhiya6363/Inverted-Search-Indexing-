# INVERTED SEARCH
### File-Based Word Indexing and Searching Application in C

## 1. Project Overview

Inverted Search is a file-based search application developed using the C programming language. It uses **Hash Tables and Singly Linked Lists** to efficiently index and search words across multiple text files.

The application reads words from input files, converts them into lowercase, and stores them in a hash table based on the first character of each word.

Each unique word is maintained in a Main Node, while its corresponding filenames and word frequencies are stored in Sub Nodes.

The application provides options to create, display, search, save and update the database through a menu-driven interface.

## 2. Objectives

- To implement an inverted indexing mechanism using C.
- To understand and implement hash tables.
- To use linked lists for dynamic data storage.
- To perform file handling operations.
- To search words and retrieve their occurrence details.
- To implement dynamic memory allocation and deallocation.
- To understand modular programming and Makefile compilation.

## 3. Technologies Used

| Technology | Purpose |
|---|---|
| C Programming | Application development |
| Hash Table | Word indexing |
| Singly Linked List | Dynamic data storage |
| File Handling | Reading and saving files |
| Dynamic Memory Allocation | Creating nodes at runtime |
| GCC Compiler | Compilation |
| Makefile | Automating compilation |

## 4. Project Architecture

The project uses a combination of three data structures:

1. File List
2. Hash Table
3. Main Node and Sub Node Linked Lists

### 4.1 File List

The file list stores the names of all validated input files.

Each node contains:
- Filename
- Link to the next node

Structure:

`node_ht`

```c
typedef struct node
{
    char f_name[MAX_FILE_NAME];
    struct node *link;
} node_ht;
```

### 4.2 Hash Table

The application uses a hash table containing 27 indices.

- Index 1 to 26 represents letters A to Z.
- Index 0 stores words beginning with non-alphabetic characters.

The hash index is calculated using the first character of the word.

Example:

| Word | Hash Index |
|---|---:|
| Apple | 1 |
| Banana | 2 |
| Cat | 3 |
| Dog | 4 |
| Orange | 15 |
| 123 | 0 |

The `get_hash_index()` function calculates the index, and `normalize_word()` converts words into lowercase.

### 4.3 Main Node

Each Main Node stores:
- Unique word
- Number of files containing that word
- Link to the next Main Node
- Link to the corresponding Sub Node list

```c
typedef struct main_node
{
    int file_count;
    char word[50];
    struct main_node *main_link;
    sub_t *sub_link;
} main_t;
```

### 4.4 Sub Node

Each Sub Node stores:
- Filename
- Number of occurrences of the word in that file
- Link to the next Sub Node

```c
typedef struct sub_node
{
    char file_name[MAX_FILE_NAME];
    int word_count;
    struct sub_node *sub_link;
} sub_t;
```

## 5. Working Principle

The application follows these steps:

1. Accept multiple filenames through command-line arguments.
2. Validate the input files.
3. Create a linked list containing validated filenames.
4. Read each file and extract words.
5. Convert each word into lowercase.
6. Calculate the hash index using the first character.
7. Search for the word in the corresponding hash-table index.
8. If the word exists, search its Sub Node list for the filename.
9. If both word and filename exist, increment the word count.
10. If the word exists but the filename is new, create a new Sub Node.
11. If the word does not exist, create a new Main Node and Sub Node.
12. Perform database operations through the menu.

## 6. Functionalities

### 6.1 File Validation

**Source file:** `read_and_validate.c`

This operation validates the input files before creating the database.

Validation includes:

- Checking whether duplicate filenames are provided.
- Checking whether the file can be opened.
- Checking whether the file is empty.
- Checking filename length.
- Creating a linked list of validated filenames.

If validation fails, the application displays an appropriate error message.

### 6.2 Create Database

**Source file:** `create_db.c`

This operation reads the contents of all validated input files and creates the inverted index.

Working steps:

1. Open each input file.
2. Read words using `fscanf()`.
3. Convert words into lowercase.
4. Calculate the hash index.
5. Search for the word in the Main Node list.
6. If the word exists, search for the filename in the Sub Node list.
7. Increment the word count if the filename already exists.
8. Otherwise, create a new Sub Node.
9. If the word does not exist, create a new Main Node and Sub Node.
10. Insert the new Main Node into the hash table.

### 6.3 Display Database

**Source file:** `display_db.c`

This operation displays the complete inverted index.

It traverses all 27 hash-table indices and displays the Main Node and corresponding Sub Node information.

The output is arranged in tabular columns.

| Index | Word | File Count | Filename | Word Count |
|---|---|---:|---|---:|
| 1 | apple | 2 | file1.txt | 3 |
| 1 | apple | 2 | file2.txt | 2 |
| 2 | banana | 1 | file1.txt | 2 |

Column descriptions:

- Index: Hash-table index.
- Word: Indexed word.
- File Count: Number of files containing the word.
- Filename: Name of the file.
- Word Count: Number of occurrences in that file.

If the database is empty, the application displays an appropriate message.

### 6.4 Search Database

**Source file:** `search_db.c`

This operation searches for a specific word in the inverted index.

Working steps:

1. Accept the search word from the user.
2. Convert the word into lowercase.
3. Calculate its hash index.
4. Traverse the corresponding Main Node list.
5. Compare the search word with stored words using `strcmp()`.
6. If the word is found, traverse its Sub Node list.
7. Display the filename and word frequency in tabular format.
8. If the word is unavailable, display an error message.

Example output:

| Word | File Count | Filename | Word Count |
|---|---:|---|---:|
| apple | 2 | file1.txt | 3 |
| apple | 2 | file2.txt | 2 |

### 6.5 Save Database

**Source file:** `save_db.c`

This operation saves the existing inverted index into a user-specified file.

The application traverses the complete hash table and writes each word along with its file count, filename and word count.

Saved database format:

```text
apple 2 file1.txt 3
apple 2 file2.txt 2
banana 1 file1.txt 2
```

The saved database can later be used by the Update Database functionality.

### 6.6 Update Database

**Source file:** `update_db.c`

This operation reads a previously saved database file and loads its records into the hash table.

Working steps:

1. Accept the saved database filename.
2. Open the file in read mode.
3. Read the word, file count, filename and word count.
4. Normalize the word.
5. Calculate its hash index.
6. Search for the word in the hash table.
7. If the word does not exist, create a new Main Node and Sub Node.
8. If the word exists, search for the filename.
9. If the filename is new, create a new Sub Node and update the file count.
10. Close the database file.

This allows previously saved index records to be loaded into the database.

### 6.7 Free Database

**Source file:** `free_db.c`

This operation releases dynamically allocated memory.

It performs two operations:

- `free_database()` – Frees all Main Nodes and their corresponding Sub Nodes in the hash table.
- `free_file_list()` – Frees all nodes in the input filename linked list.

This helps prevent memory leaks during normal program termination.

## 7. Project File Structure

```text
Inverted_Search/
│
├── main.c
├── create_db.c
├── display_db.c
├── search_db.c
├── update_db.c
├── save_db.c
├── free_db.c
├── hash_index.c
├── read_and_validate.c
│
├── inverted_search.h
├── Makefile
│
├── file1.txt
├── file2.txt
└── file3.txt
```

### File Descriptions

| File | Responsibility |
|---|---|
| main.c | Menu-driven main program |
| read_and_validate.c | Input file validation |
| create_db.c | Inverted index creation |
| display_db.c | Display complete database |
| search_db.c | Search for a word |
| save_db.c | Save database records |
| update_db.c | Load and update database records |
| hash_index.c | Hash-index calculation and normalization |
| free_db.c | Memory deallocation |
| inverted_search.h | Structure definitions, macros and function declarations |
| Makefile | Automates compilation |

## 8. Compilation Using Makefile

The project uses a Makefile to automate the compilation of multiple C source files.

The Makefile generates object files and links them into an executable named `a.out`.

Commands:

```bash
make
```

Compiles the project.

```bash
./a.out file1.txt file2.txt file3.txt
```

Executes the application with three input files.

```bash
make clean
```

Removes generated object files and the executable.

## 9. Menu-Driven Application

After successful file validation, the application displays the following menu:

```text
================= INVERTED SEARCH =================

1. Create Database
2. Display Database
3. Search Database
4. Save Database
5. Update Database
6. Exit

Enter your choice:
```

The user selects an operation by entering the corresponding number.

## 10. Concepts Learned

Through this project, the following C programming concepts are implemented:

- Structures and nested structures.
- Pointers and pointer manipulation.
- Singly linked lists.
- Hash tables and hashing.
- Dynamic memory allocation using `malloc()`.
- Memory deallocation using `free()`.
- File handling using `fopen()`, `fscanf()`, `fprintf()` and `fclose()`.
- String handling using `strcmp()` and `strcpy()`.
- Modular programming.
- Header files and function declarations.
- Compilation and linking using GCC.
- Makefile automation.

## 11. Conclusion

The Inverted Search project demonstrates the practical implementation of hash tables and linked lists in C programming.

It provides an efficient way to organize words from multiple text files and retrieve their occurrence information. The project also strengthens understanding of pointers, dynamic memory allocation, file handling, data structures and modular programming.

This project helped develop practical knowledge of implementing data structures and managing dynamic data using C.
