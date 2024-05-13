// Implement a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represent a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 1125;

// Hash table
node *table[N];

// Keep track of amount of words in dictionary
int words_amount = 0;

// Load dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    // Read word by word in file, until no more words found
    while (fscanf(dict, "%s", word) == 1)
    {
        // Allocate node for word and hash it
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(dict);
            return false;
        }

        int index = hash(word);

        // Put word in node, and insert it at beggining of linked list in corresponding index of table
        strcpy(n->word, word);
        n->next = table[index];
        table[index] = n;

        words_amount++;
    }

    fclose(dict);
    return true;
}

// Return number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words_amount;
}

// Hash word to a number
unsigned int hash(const char *word)
{
    // Sum ASCII values of word's letters
    int sum = 0;

    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (isalpha(word[i]))
        {
            sum += toupper(word[i]) - 'A';
        }
    }

    // Enough hash numbers to all possibilites of sum: 25 (z value) * 45 (max word length)
    return sum % 1125;
}

// Return true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);

    // Set pointer to beggining of linked list at corresponding index in table, then iterate over it
    for (node *ptr = table[index]; ptr != NULL; ptr = ptr->next)
    {
        // If pointer points to node that contains word (case insensitive), word is in dictionary
        if (!strcasecmp(ptr->word, word))
        {
            return true;
        }
    }

    return false;
}

// Unload dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over table
    for (int i = 0; i < N; i++)
    {
        // Iterate over linked list of table's index, freeing each node
        while (table[i] != NULL)
        {
            node *ptr = table[i]->next;

            free(table[i]);

            table[i] = ptr;
        }
    }

    return true;
}
