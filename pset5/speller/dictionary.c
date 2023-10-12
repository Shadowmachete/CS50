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
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
FILE *dict = NULL;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashNum = hash(word);
    char buffer[50];
    fseek(dict, 0, SEEK_SET);
    while (fgets(buffer, sizeof(buffer), dict))
    {
        buffer[strcspn(buffer, "\n")] = 0;
        if (strcasecmp(word, buffer) == 0)
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
    int sum = 0;
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        sum += toupper(word[i]);
    }
    return (int) ((sum / strlen(word)) + sum) % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    char buffer[50];
    while (fgets(buffer, sizeof(buffer), dict))
    {
        buffer[strcspn(buffer, "\n")] = 0;
        int hashedInt = hash(buffer);
        printf("%s %i %s\n", buffer, hashedInt, table[hashedInt]->word);
        if (table[hashedInt]->word != NULL)
        {
            table[hashedInt].word = buffer;
        }
        else
        {
            printf("Collision");
        }
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (dict == NULL)
    {
        return 0;
    }
    char buffer[50];
    int counter = 0;
    fseek(dict, 0, SEEK_SET);
    while (fgets(buffer, sizeof(buffer), dict))
    {
        counter++;
    }
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
    }
    if (table[N-1] == NULL)
    {
        fclose(dict);
        return true;
    }
    fclose(dict);
    return false;
}
