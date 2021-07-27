#include <cs50.h>  // get_string
#include <ctype.h> // isalpha isdigit islower tolower toupper
#include <stdio.h> // printf
#include <stdlib.h> // atoi
#include <string.h> // strlen


void rot(int n, string s);
bool str_isdigit(string s);


int main(int argc, string argv[])
{
    // arg check
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else if (!str_isdigit(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int num = atoi(argv[1]);
    // get user's plaintext
    string plaintext = get_string("plaintext: ");
    // print out the ciphertext
    printf("ciphertext: ");
    rot(num, plaintext);
}



void rot(int n, string s)
{
    char t;
    n = n % 26;
    for (int i = 0, l = strlen(s); i < l; i++)
    {
        if (isalpha(s[i]))
        {
            t = ((((int) toupper(s[i]) - 65) + n) % 26) + 65;
            if (islower(s[i]))
            {
                printf("%c", tolower(t));
            }
            else
            {
                printf("%c", t);
            }
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
}


bool str_isdigit(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false; // 0
        }
    }
    return true; // 1
}
