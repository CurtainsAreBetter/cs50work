#include <cs50.h>
#include <stdio.h>



int main(void)
{
    // Get start population and only accept integers > or = to 9
    int s;
    do
    {
        s = get_int("Start size: ");
    }
    while (s < 9);

    // Get end population. Only accept if larger than start population
    int e;
    do
    {
        e = get_int("End size: ");
    }
    while (e < s);

    // Calculate years it will take for population reach end pop
    int y = 0;
    while (s < e)
    {
        float g = s / 3.0;
        float d = s / 4.0;
        s += (int) g - (int)d;
        y++;
    }

    // Print the found number of years
    printf("Years: %i\n", y);
}
