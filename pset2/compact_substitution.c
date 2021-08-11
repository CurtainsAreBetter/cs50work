#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main( int argc, string argv[])
{
    if (argc != 2)  // validate the arguments
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        int alcount[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (int i = 0; i < 26; i++)
        {
            if (isalpha(argv[1][i]))
            {
                int index = (int) toupper(argv[1][i]) - 65;
                alcount[index] += 1;
                if (alcount[index] > 1)
                {
                    printf("Key must contain each letter of the alphabet.\n");
                    return 1;
                }
            }
            else
            {
                printf("Key must only contain letters.\n");
                return 1;
            }
        }
        for (int i = 0; i < 26; i++)
        {
            if (!alcount[i])
            {
                printf("Key must contain each letter of the alphabet.\n");
                return 1;
            }
        }

    }
    string ptext = get_string("plaintext: ");  // begin enciphering (doubt that's a word)
    printf("ciphertext: ");
    for (int i = 0, n = strlen(ptext); i < n; i++)
    {
        if (isalpha(ptext[i]))
        {
            char h = toupper(argv[1][(int) toupper(ptext[i])-65]);
            if ((int) ptext[i] > 96)
            {
                h = tolower(h);
            }
            printf("%c", h);
        }
        else
        {
            printf("%c", ptext[i]);
        }
    }
    printf("\n");
}
