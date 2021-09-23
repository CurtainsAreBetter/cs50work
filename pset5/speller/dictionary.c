// Implements a dictionary's functionality
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

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

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // hash word
    //unsigned int index = hash(word); moved to the for loop
    // go through linked list to see if word exists
    for (node *n = table[hash(word)]; n != NULL; n = n->next)
    {
        if (!strcasecmp(word, n->word))
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int l1 = tolower(word[0]) - 97;
    int l2 = word[1];
    int l3;
    if (l2 == '\0' || l2 == '-')
    {
        return 17575;
    }
    else if (word[2] == '\0' || word[2] == '-')
    {
        return 17575;
    }
    l2 = tolower(l2) - 97;
    l3 = tolower(word[2]) - 97;
    
    return (l1 * 676) + (l2 * 26) + l3;
}

unsigned int _d_word_count = 0;
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open file
    FILE *file = fopen(dictionary, "r");
    // check to see if successful
    if (file == NULL)
    {
        printf("Error: Failure to open file\nFile %s is NULL.\n", dictionary);
        return false;
    }

    // fsanf returns 1 until it hits EOF
    // whenver for loop logic is checked, buffer also gets updated
    // every loop leads to _d_word_count going up by 1, keeping track
    // of dicitonary word count
    // Considering where I started, I'm happy that I came up with
    // this for loop
    for (char buffer[LENGTH + 1]; fscanf(file, "%s", buffer) == 1; _d_word_count++)
    {
        // create a node, add word to node
        node *tmp = malloc(sizeof(node));
        if (tmp == NULL)
        {
            printf("Memory allocation error at line %i of file: %s.\n", _d_word_count, dictionary);
            return false;
        }
        strcpy(tmp->word, buffer);

        // hash word to determine which index of table to add node to
        unsigned int index = hash(buffer);
        node *base = table[index];

        // set tmp->next to base's location
        tmp->next = base;
        // tmp now points at base
        // set table[index] to be tmp
        table[index] = tmp; // I feel like this irradicates what was there

    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return _d_word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    int f_count = 0;
    for (int i = 0; i < N; i++)
    {

        for (node *base = table[i]; base != NULL; f_count++)
        {
            node *tmp = base->next;
            free(base);
            base = tmp;
        }
    }
    // like valgrind, this just compares the malloc count and free count
    if (f_count - _d_word_count)
    {
        return false;
    }
    return true;

}
