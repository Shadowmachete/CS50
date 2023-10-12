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
    node *ptr = table[hashNum];
    while (ptr != NULL)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    free(ptr);
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
        if (table[hashedInt] == NULL)
        {
            node *new_node = malloc(sizeof(node));
            if (new_node == NULL)
            {
                return 1;
            }
            for (int i = 0; i < LENGTH + 1; i++)
            {
                new_node->word[i] = buffer[i];
            }
            new_node->next = NULL;
            table[hashedInt] = new_node;
        }
        else
        {
            node *ptr = table[hashedInt];
            while (ptr->next != NULL)
            {
                ptr = ptr->next;
            }

            node *new_node = malloc(sizeof(node));
            if (new_node == NULL)
            {
                return 1;
            }
            for (int i = 0; i < LENGTH + 1; i++)
            {
                new_node->word[i] = buffer[i];
            }
            new_node->next = NULL;
            ptr->next = new_node;
        }
    }
    for (int i = 0; i < N; i++)
    {
        printf("%s", table[i]->word);
        printf("\n");
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
            node *next = ptr->next;
            free(ptr);
            ptr = next;
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
