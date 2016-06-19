#include <cs50.h>
#include <stdio.h>
#include <math.h>
int main(void)
{
    float change = -1; 
    int temp = -1, cntr=0;
    do
    {
        printf ("How much change is owed?\n");
        change = GetFloat();
    }while (change < 0);
    // Rounding off the value
    temp = (round(change * 100));
    // Applying Greedy Algorithm
    while( temp != 0)
    {
        if (temp >= 25)
            temp = temp - 25;
        else if (temp >= 10)
            temp = temp - 10;
        else if (temp >= 5)
            temp = temp - 5;
        else if (temp >= 1)
            temp = temp - 1; 
        // Increasing the number of coins used
        ++cntr; 
    }
    printf("%d\n", cntr);
    return 0;
}
