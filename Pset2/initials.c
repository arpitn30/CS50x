#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
int main(void)
{
    string Name;
    Name = GetString(); 
    printf ("%c", (char) toupper(Name[0]));
    for (int i = 1; Name[i] != '\0'; i++)
    {
        if (Name[i] == ' ')
        {
            printf ("%c", (char) toupper(Name[i + 1]));
        }
    }
    printf("\n");
    return 0;
}
