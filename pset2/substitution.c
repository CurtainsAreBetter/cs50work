#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Checks key to make sure each letter of
// the alpha is present once and only once
bool has_each_letter(string key);
// Checks if a string only contains letters
bool str_isalpha(string s);
// Prints a ciphertext from given
// plaintext and key
void print_cipher(string ptext, string key);
// Turns every char in a string's case to upper
void str_toupper(string s);


int main(int argc, string argv[])
{
    // key validity checks
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else if (!str_isalpha(argv[1]))
    {
        printf("Key must only contain letters of the alphabet.\n");
        return 1;
    }
    else if (!has_each_letter(argv[1]))
    {
        printf("Each letter of the alphabet must be present in your key.\n");
        return 1;
    }
    // end key validity check
    // set key to be all uppercase
    str_toupper(argv[1]);
    // request plaintext
    string user = get_string("plaintext: ");
    // print ciphertext
    printf("ciphertext: ");
    print_cipher(user, argv[1]);
    return 0;
}


bool has_each_letter(string key)
{
    /*
    Each index of alcount reps a letter in the alphabet where a is i=0, z is i=25
    When a letter is seen, its count is added to its respective index of alcount
    We want each letter to be used once. No more, no less.
    */
    int alcount[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 26; i++)  // we should know by now that the key is len 26
    {
        int index = (int) toupper(key[i]) - 65;
        alcount[index] += 1;
        if (alcount[index] > 1)
        {
            return false;
        }
    }
    for (int i = 0; i < 26; i++)
    {
        if (!alcount[i])
        {
            return false;
        }
    }
    return true;
}


bool str_isalpha(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isalpha(s[i]))
        {
            return false;
        }
    }
    return true;
}


// print cipher text out
// doesn't save to memory
void print_cipher(string ptext, string key)
{
    char h;
    for (int i = 0, n = strlen(ptext); i < n; i++)
    {
        // check if char is a letter
        if (isalpha(ptext[i]))
        {
            // do conversion
            h = key[(int) toupper(ptext[i]) - 65];
            // check if ptext char is lower case.
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


void str_toupper(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        s[i] = toupper(s[i]);
    }
}

