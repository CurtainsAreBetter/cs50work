#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string s = get_string("Text: ");
    // init counts
    float letters = 0.0;
    float sentences = 0.0;
    float words = 0.0;
    char last;

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalpha(s[i]))
        {
            letters += 1;
        }
        // not a letter so check if end of sentence
        else if (s[i] == '!' || s[i] == '?' || s[i] == '.')
        {
            sentences += 1;
        }
        // not an end of sentence so check for spaces and ignore double spaces.
        else if (s[i] == ' ' && last != ' ')
        {
            words += 1;
        }
        last = s[i];
    }
    // add 1 to words because final word doesn't have a space following it
    words += 1;

    // now for the math
    // index = 0.0588 * L - 0.296 * S - 15.8
    float L = (letters / words) * 100;
    float S = (sentences / words) * 100;

    float grade = (0.0588 * L) - (0.296 * S) - 15.8;
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", grade);
    }
}

