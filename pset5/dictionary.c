// Implements a dictionary's functionality

#include <stdbool.h>

//Added by Me
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Gets the hash value of the word supplied
    // sets the cursor to the index of the array (A-Z)
    int hashNum =  hash(word);
    node *cursor = table[hashNum];
    node *tmp = NULL;
    // If the given index is null then there are no words in the dictionary that start
    // with that lettter
    if (table[hashNum] == NULL)
    {
        return false;
    }
    else
    {
        while (cursor != NULL)
        {
            //sets the temporary value to the value of the cursor
            tmp = cursor;
            //increments the value of the cursor to the next value in the linked list
            cursor = cursor->next;
            //compares the current word to the input and returns true if they match
            if (strcasecmp(tmp->word, word) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // gets the first letter of the char/String supplied
    char first =  word[0];
    //container is the bucked that the word will go into in the Hash Table
    //   : container is initially set to 0 and 'a' is not included in the switch because 
    //          because a is equal to 0 in the Hash Table
    int container = 0;
    switch (tolower(first))
    {
        case 'b':
            container = 1;
            break;
        case 'c':
            container = 2;
            break;
        case 'd':
            container = 3;
            break;
        case 'e':
            container = 4;
            break;
        case 'f':
            container = 5;
            break;
        case 'g':
            container = 6;
            break;
        case 'h':
            container = 7;
            break;
        case 'i':
            container = 8;
            break;
        case 'j':
            container = 9;
            break;
        case 'k':
            container = 10;
            break;
        case 'l':
            container = 11;
            break;
        case 'm':
            container = 12;
            break;
        case 'n':
            container = 13;
            break;
        case 'o':
            container = 14;
            break;
        case 'p':
            container = 15;
            break;
        case 'q':
            container = 16;
            break;
        case 'r':
            container = 17;
            break;
        case 's':
            container = 18;
            break;
        case 't':
            container = 19;
            break;
        case 'u':
            container = 20;
            break;
        case 'v':
            container = 21;
            break;
        case 'w':
            container = 22;
            break;
        case 'x':
            container = 23;
            break;
        case 'y':
            container = 24;
            break;
        case 'z':
            container = 25;
            break;
    }
    return container;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Opens the file
    FILE *dFile = fopen(dictionary, "r");
    node *n;
    char readWord[LENGTH + 1];
    int index;
    
    // Checks if the file is NULL and Exits the program if it is
    if (dFile == NULL)
    {
        return false;
    }
    else
    {
        // Nulls the array to store the dictionary
        // for (int i = 0; i < N; i++)
        // {
        //     table[i] = NULL;
        // }
        // Reads through the open file
        while (fscanf(dFile, "%s", readWord) != EOF)
        {
            node *tmp;
            // allocates space in memory to n
            n = malloc(sizeof(node));
            // if memeory allocation fails then return false
            if (n == NULL)
            {
                return false;
            }
            
            // otherwise coppy the intake word into n->word and sets the value of n->next to null
            strcpy(n->word, readWord);
            n->next = NULL;
    
            // gets the index for the Hash Table that the word will be inserted at
            index = hash(n->word);

            if (table[index] == NULL)
            {
                table[index] = n;
            }
            else
            {
                
                n->next = table[index];
                table[index] = n;
            }
        }
    }
    fclose(dFile);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    node *tmp = NULL;
    int count = 0;
    
    for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }
        else
        {
            for (tmp = table[i]; tmp != NULL; tmp = tmp->next)
            {
                count++;
            }
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor;
    node *tmp;
    // TODO
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        tmp = table[i];
        while (cursor != NULL)
        {
            cursor = cursor -> next;
            free(tmp);
            tmp = cursor;
        } 
    }
    return true;
}
