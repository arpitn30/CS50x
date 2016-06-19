#include <stdio.h>
#include <cs50.h>
int main(void)
{
    int height = 0;
    do
    {
        printf("Height: ");
       // Takes height of pyramid as input
        height = GetInt(); 
    }while(height < 0 || height > 23);
    for(int i = 0; i < height; i++)
    {
        // Loop for spaces
        for(int j = 0; j < height - 1 - i; j++)
            printf(" ");
        // Loop for hashes
        for(int k = 0; k < i + 2; k++)
            printf("#");
        printf("\n");
    }
    return 0;
}
