// Implements a dictionary's functionality

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 64;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}
int count = 0;
// Hashes word to a number
unsigned int hash(const char *word)
{
    // printf("hash called\n");
    int hashnum = word[0];
    if (hashnum != 0)
    {
        // printf("hashnum set\n");
    }
    for (int i = 0; word[i] == 0; i++)
    {
        hashnum *= word[i];
        // printf("hash got to letter %i\n", i + 1);
    }
    // printf("hash loop escaped\n");
    hashnum = (hashnum % 64) - 1;
    return hashnum;
}

// Loads dictionary into memory, returning true if successful, else false

bool load(const char *dictionary)
{
    FILE *infile = fopen(dictionary, "r");
    if (infile == NULL)
    {
        return false;
    }
    printf("file open\n");
    char *word = malloc(LENGTH + 1);
    while (count > -1)
    {
        count++;
        if (fscanf(infile, "%s", word) == EOF)
        {
            // printf("file closed\n");
            fclose(infile);
            return true;
        }
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);
        n->next = NULL;
        // printf("node made\n");
        if (table[hash(n->word) - 1] != NULL)
        {
            n->next = table[hash(n->word) - 1];
            table[hash(n->word) - 1] = n;
        }
    }
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool free_node(struct node *n)
{
    if (n->next != NULL)
    {
        free_node(n->next);
    }
    else
    {
        free(n);
        count--;
    }
    return true;
}
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        free_node(table[i]);
    }
    if (count == 0)
    {
        return true;
    }
    return false;
}
