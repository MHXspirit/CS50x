// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26 + 26;

// Hash table
node *table[N] = {0};

// Size of dictionary
unsigned int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word
    unsigned int index = hash(word);

    // Traverse linked list and check
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    if (strlen(word) < 2)
    {
        return toupper(word[0]) - 'A' + 26 * 26;
    }
    else if (word[0] == '\'')
    {
        return (toupper(word[1]) - 'A') * 26 + toupper(word[2]) - 'A';
    }
    else
    {
        return (toupper(word[0]) - 'A') * 26 + toupper(word[1]) - 'A';
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fclose(file);
        return false;
    }

    // Read strings from file and put it into hash table
    char buffer[LENGTH + 1];
    while (fscanf(file, "%s", buffer) != EOF)
    {
        // Create a node
        node *tmp = malloc(sizeof(node));
        if (tmp == NULL)
        {
            fclose(file);
            return false;
        }

        strcpy(tmp->word, buffer);
        tmp->next = NULL;

        // Hash word
        unsigned int index = hash(buffer);

        // Insert node into hash table and update the size
        tmp->next = table[index];
        table[index] = tmp;
        count ++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    int index;
    for (index = 0; index < N; index ++)
    {
        node *tmp = table[index];
        node *cursor = table[index];
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }

    if (index == N)
    {
        return true;
    }
    else
    {
        return false;
    }
}