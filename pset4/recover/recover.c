#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int header_check(BYTE heads[512]);
void filenamer(char s[], int *count);

int main(int argc, char *argv[])
{
    // Verify user entry
    if (argc != 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }

    // Open data file
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Error: Unable to open %s\n", argv[1]);
        return 1;
    }

    // Initiate the outfile, outfilename and declare the filecount
    FILE *outfile;
    char outname[8];
    int filecount = 0;

    // Begin going through the data file
    // 512 bytes at a time (called blocks)
    BYTE block[512];
    while (fread(block, sizeof(BYTE), 512, infile))
    {
        // For each block, check for the jpg header
        if (!header_check(block))
        {
            // If a header is found, check if this is the first header (filecount would equal 0)
            if (filecount == 0)
            {
                // If it's the first, assign outfile to file 000.jpg
                // by using namer. This will also update file count
                filenamer(outname, &filecount);
                outfile = fopen(outname, "w");
                // Verify the file was opened without error
                if (outfile == NULL)
                {
                    printf("Error: Could not print to file: %s\n", outname);
                    fclose(infile);
                    return 1;
                }
            }
            else
            {
                // If not, close current outfile, open new outfile, and then update fcount and name
                fclose(outfile);
                filenamer(outname, &filecount);
                outfile = fopen(outname, "w");
            }
        }
        // Check if filecount is greater than 0
        if (filecount > 0)
        {
            // If so, write current block to outfile, otherwise do nothing
            fwrite(&block, sizeof(BYTE), 512, outfile);
        }
    }
    // close all files
    fclose(infile);
    fclose(outfile);
}

// Returns 0 if start of block is a jpg header, returns 1 otherwise
int header_check(BYTE heads[512])
{
    // check first three bytes
    if (heads[0] == 0xff && heads[1] == 0xd8 && heads[2] == 0xff)
    {
        // check final byte if it's worth it
        char buffer[3];
        sprintf(buffer, "%hx", heads[3]);
        if (buffer[0] == 'e')
        {
            return 0;
        }
    }
    return 1;
}

// name changes the given string
// and updates count


// when you run filenamer
// the string is updated for the next file name
// and the count is set up by one
// so if you are assigning as string with this funtion and your count is at 5
// you will get '005.jpg'
// and your count will be set to 6
void filenamer(char s[], int *count)
{
    sprintf(s, "%03d.jpg", *count);
    *count = *count + 1;
}
