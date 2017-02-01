/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

#define MaxWord 45
#define ASCIIa 97

typedef struct node
{
    bool isWord;    // Checks whether a word is complete or not
    struct node* Alph[27];   // 26 letters + apostrophe
}node;

unsigned int dictSize = 0;
node* Root = NULL;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO

    node* Next = Root;
    char ch = 0;
    int i = 0;

    while(word[i] != '\0')
    {
        ch = word[i];
        tolower(ch);
		
		if(i > MaxWord)
			return true;
        else if((ch >= 'a' && ch <= 'z') || (ch == '\''))
        {
            if(Next->Alph[ch - ASCIIa] == NULL)
                return false;
            else
                Next = Next->Alph[ch - ASCIIa];
        }
        else
            return true;
        i++;
    }
    return Next->isWord;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* Dict = fopen(dictionary, "r");
    if (Dict == NULL)
    {
        printf("Error opening dictionary file %s.\n", dictionary);
        return false;
    }
    char word[27];
    int index = 0;

    Root = (node*) malloc(sizeof(node));

    // read in one char at a time until EOF is reached
    for (int ch = fgetc(Dict); ch != EOF; ch = fgetc(Dict))
    {
        if (ch != '\n')
        {
            word[index] = ch;
            index++;
        }
        else
        {
            word[index] = ch;       // get newline char
            node* Next = Root;

            for (int i = 0; i <= index; i++)
            {
                // check for alphabetic letter
                if (isalpha(word[i]))
                {
                    // if NULL, malloc a new node for this letter
                    if (Next->Alph[word[i] - 'a'] == NULL)
                    {
                        Next->Alph[word[i] - 'a'] = (node*) malloc(sizeof(node));
                    }
                    Next = Next->Alph[word[i] - 'a'];
                }
                // check for apostrophe
                else if (word[i] == '\'')
                {
                    // if NULL, malloc a new node at the end for the '
                    if (Next->Alph[26] == NULL)
                    {
                        Next->Alph[26] =
                            (node*) malloc(sizeof(node));
                    }
                    Next = Next->Alph[26];
                }
                else if (word[i] == '\n')
                {
                    Next->isWord = true;
                }
            }
            index = 0;
            dictSize++;
        }
    }

    fclose(Dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return dictSize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
void del(node* Next)
{
    for(int i = 0; i <= 26; i++)
    {
        if(Next->Alph[i] != NULL)
            del(Next->Alph[i]);
    }
    free(Next);
}
bool unload(void)
{
    // TODO
    del(Root);
    return true;
}
