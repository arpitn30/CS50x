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
        string k = argv[1], crypto;
        int len = strlen(k), k2;
        for(int i = 0; i < len; i++)
            if(!(isalpha(k[i])))
            {
                printf("Keyword must be only A-Z and a-z");
                return 1;
            }
        crypto = GetString();
        for (int i = 0, j = 0; crypto[i] != '\0' ; i++)
        {
            if(isalpha(crypto[i]))
            {
                if(isupper(k[j]))           k2 = k[j] - 65;
                else if(islower(k[j]))      k2 = k[j] - 97;

                if(isupper(crypto[i]))
                {
                    crypto[i] -= 65;
                    crypto[i] = (crypto[i] + k2) % 26;
                    crypto[i] += 65;
                }
                else
                {
                    crypto[i] -= 97;
                    crypto[i] = (crypto[i] + k2) % 26;
                    crypto[i] += 97;
                }
                j = (j + 1) % len;
            }
            printf("%c",crypto[i]);
        }
        printf("\n");
     return 0;
     }   
}
