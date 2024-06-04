// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef int16_t SAMPLE;

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

    float factor = atof(argv[3]);

    // Create an array of unsigned bytes the length of the header (44 in this case)
    uint8_t header[HEADER_SIZE];
    // read the header from the input file into the header array we just defined
    fread(header, HEADER_SIZE, 1, input);
    // write from the header array to the output file
    fwrite(header, HEADER_SIZE, 1, output);

    // create a buffer the size of a single sample, which we defined earlier to be the size of a
    // signed 16 bit integer.
    SAMPLE buffer;
    // while the read in sample is not 0 (null), keep reading
    while (fread(&buffer, sizeof(SAMPLE), 1, input) != 0)
    {
        // because we called fread from inside the while loop's conditional (no, I don't like it
        // either), the buffer contains the next sample to write. we then multiply the sample by the
        // scaling factor, and then write that buffer to the output file.
        buffer *= factor;
        fwrite(&buffer, sizeof(SAMPLE), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
