#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>     // for atoi()
#include <string.h>     // for strlen()
#include <ctype.h>      // for isupper()
int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./caesar <key>\n");
        return 1;
    }
    else
    {
        int k = atoi(argv[1]);      // atoi converts a string into int
        string crypto;
        crypto = GetString()  ;
        for (int i = 0; crypto[i] != '\0' ; i++)
        {
            if(isalpha(crypto[i]))
            {
                for(int p = 0; p < k; p++)
                {
                    crypto[i] += 1;
                    if(crypto[i] > 'z')
                        crypto[i] = 96 + (crypto[i] - 'z');
                    else if (crypto[i] > 'Z' && crypto[i] < 'a')
                        crypto[i] = 64 + (crypto[i] - 'Z');
                 }
            }
            printf("%c",crypto[i]);
        }
        printf("\n");
     return 0;
     }   
}
