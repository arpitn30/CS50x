/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if(n < 0)
        return false;
    else
    {   int min = 0, max = n;
        while(max >= min)
        {
            int mp = (max + min) / 2;
            if(values[mp] < value)
                min = mp + 1;
            else if(values[mp] > value)
                max = mp - 1;
            else
                return true;
        }
        return false;  
    }
}


/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    for( int i = 1; i < n; i++)
    {
        int ele = values[i];
        int j = i;
        while ((j > 0) && (values[j-1] > ele))
        {
            values[j] = values[j-1];
            j--; 
        }
        values[j] = ele;
    }
    return;
}
