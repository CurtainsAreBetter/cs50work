// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // atof converts a string into a float
    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // Well I mean we can directly copy bight for bight with a for loop that that runs 44 times

    // This is to copy the 44 bytes
    // A while loop would work if we meant to copy the whole thing but we don't so
    // Just the header for now
    // personally I thinka while loop would be fine, just have a counter and if statements
    // but I'd rather follow the todo comments
    uint8_t byte;
    for (int i = 0; i < HEADER_SIZE; i++)
    {
        // so set 'byte' to the og byte
        // technically arg 2 could be just '1' but I'm being careful
        fread(&byte, sizeof(uint8_t), 1, input);
        // byte now holds the byte of information we want to transfer over
        // then write it to the new file
        fwrite(&byte, sizeof(uint8_t), 1, output);
    }
    // that should be copied then right?
    // TODO: Read samples from input file and write updated data to output file

    // will fread start at the header from here or will I have to like direct it to go to
    // byte 44 and beyond

    // while loop should work from here on out
    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        // do the math on the buffer
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
