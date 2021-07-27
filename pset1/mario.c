#include <cs50.h>
#include <stdio.h>

//Intake an int. Only accept 1-8.
// Make a pyramid of that height. Twice that width plus two spaces.

int main(void)
{
    // Get height between 1 and 8
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 1 || h > 8);

    // Set hash and space counts for the loops
    int h_count = 1;
    int space_count = h - 1;
    //Loop h times (So 1-8 depending on user input)
    for (int i = 0; i < h; i++)
    {
        // Loops for the proper amount of spaces
        for (int j = 0; j < space_count; j++)
        {
            printf(" ");
        }
        //print first hashes
        for (int j = 0; j < h_count; j++)
        {
            printf("#");
        }
        // Center space
        printf("  ");
        // print hashes on right side
        for (int j = 0; j < h_count; j++)
        {
            printf("#");
        }
        // spaces aren't really needed so straight to a new line
        printf("\n");
        // Update the counts for the next layer
        space_count--;
        h_count++;
    }



}
