// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *list = table[index];
    for (node *cursor = list; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");

    // Check if the return value is NULL
    if (source == NULL)
    {
        return false;
    }

    char tmp_word[LENGTH + 1];
    node *list = NULL;

    // Read each word in the file
    while (fscanf(source, "%s", tmp_word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, tmp_word);

        // Add each word to the hash table
        unsigned int index = hash(n->word);
        list = table[index];
        n->next = list;
        table[index] = n;

        dict_size++;
    }

    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *list = table[i];
        node *cursor = list;
        node *tmp = cursor;

        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            if (tmp == NULL)
            {
                return false;
            }

            free(tmp);
        }
    }
    return true;
}
