// Implements a dictionary's functionality
// Status: NOT WORKING, Segmentation Fault,
// WHY Submitting: Couldn't find error in my 'dictionary.c', looks all good TO ME
// ANY SUGGESTIONS APPRICIATED

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 17576;

// Hash table
node *table[N];

// Counter to size how many words are loaded in dictiionary
int *count = NULL;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    // TODO
    bool matched = false;
    unsigned int hashIndex = hash(word);

    for(node *cursor = table[hashIndex]; cursor != NULL; cursor = cursor->next)
    {
        if(strcasecmp(word, cursor->word) == 0)
        {
            matched = true;
            break;
        }
    }
    return matched;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int hashValue, value[3];

    for(int i = 0; i < 3; i++)
    {
        //Check if input is alphabet
        if(isalpha(word[i]) != 0)
        {
            if(isupper(word[i]))
            {
                value[i] = (word[i] - 65) % 26;
            }
            else if(islower(word[i]))
            {
                value[i] = (word[i] - 97) % 26;
            }
        }
    }

    hashValue = (value[0] * 676) + (value[1] * 26) + (value[2] * 1);

    return hashValue;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *infile = fopen("dictionaries/small", "r");
    if(infile == NULL)
    {
        return false;
    }

    char *buffer = NULL;

    *count = 0;
    while(fscanf(infile, "%s", buffer))
    {
        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            return false;
        }

        //copy the word into new node from buffer
        strcpy(n->word, buffer);
        n->next = NULL;

        //Get hashIndex
        unsigned int hashIndex;
        hashIndex = hash(buffer);

        //insert the word at the begining of hashIndex in table
        n->next = table[hashIndex];
        table[hashIndex] = n;

        *count = *count + 1;
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int size = *count;
    return size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    bool destroyed = false;
    for(int i = 0; i < N; i++)
    {
        while(table[i] != NULL)
        {
            node *temp = table[i]->next;
            free(table[i]);
            table[i] = temp;
            destroyed = true;
        }
    }
    return destroyed;
}
