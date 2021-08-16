#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int header_check(BYTE heads[512]);
void filenamer(char s[], int *count);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Error: Unable to open %s\n", argv[1]);
        return 1;
    }
    FILE *outfile;
    char outname[8];
    int filecount = 0;

    BYTE block[512];
    while (fread(block, sizeof(BYTE), 512, infile))
    {
        if (!header_check(block))
        {
            if (filecount == 0)
            {
                filenamer(outname, &filecount);
                outfile = fopen(outname, "w");
                if (outfile == NULL)
                {
                    printf("Error: Could not print to file: %s\n", outname);
                    fclose(infile);
                    return 1;
                }
            }
            else
            {
                fclose(outfile);
                filenamer(outname, &filecount);
                outfile = fopen(outname, "w");
            }
        }
        if (filecount > 0)
        {
            fwrite(&block, sizeof(BYTE), 512, outfile);
        }
    }
    fclose(infile);
    fclose(outfile);
}

int header_check(BYTE heads[512])
{
    if (heads[0] == 0xff && heads[1] == 0xd8 && heads[2] == 0xff)
    {
        char buffer[3];
        sprintf(buffer, "%hx", heads[3]);
        if (buffer[0] == 'e')
        {
            return 0;
        }
    }
    return 1;
}

void filenamer(char s[], int *count)
{
    sprintf(s, "%03d.jpg", *count);
    *count = *count + 1;
}
